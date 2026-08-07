# Compilação dos programas

O Makefile em `benchmarks` transforma código C e Assembly em duas imagens de
memória que podem ser carregadas pelo SoC. A construção utiliza a GNU toolchain
RISC-V configurada para `rv32i/ilp32`.

## Comandos principais

Partindo da raiz do repositório:

```bash
source env.sh
cd benchmarks
```

Um benchmark específico pode ser preparado com:

```bash
make dhrystone.pipeline.hex
make coremark.pipeline.hex
make raystones.pipeline.hex
```

Para preparar todos eles, use:

```bash
make all
```

A regra `clean` remove todo o diretório `benchmarks/build`:

```bash
make clean
```

O Makefile de simulação chama automaticamente o alvo correspondente ao valor de
`BENCHMARK`. Portanto, não é necessário executar esses comandos manualmente
antes de usar `make` em `sim`.

## Configuração da toolchain

O arquivo `common.mk` concentra os caminhos e valores compartilhados. Os
principais são:

- **`RISCV`:** diretório da toolchain, com valor padrão `.tools/riscv`;
- **`TOOLCHAIN_PREFIX`:** prefixo dos executáveis, por padrão
  `riscv64-unknown-elf`;
- **`ARCH`:** arquitetura de destino, por padrão `rv32i`;
- **`ABI`:** ABI utilizada, por padrão `ilp32`;
- **`BUILD`:** diretório dos artefatos, por padrão `benchmarks/build`.

Esses valores podem ser substituídos na linha de comando. Por exemplo:

```bash
make coremark.pipeline.hex RISCV=/opt/riscv ARCH=rv32i ABI=ilp32
```

O prefixo é usado para localizar `gcc`, `as`, `ld`, `objdump` e `objcopy`. O GCC
também é consultado para encontrar as versões de `libm` e `libgcc` compatíveis
com a arquitetura e a ABI selecionadas.

## Como ler as regras

Uma regra do Make possui um alvo, suas dependências e os comandos usados para
produzi-lo:

```make
alvo: dependencias | diretorios
	comando entrada saida
```

O alvo só é reconstruído quando não existe ou quando uma de suas dependências é
mais recente. Dependências após `|` são usadas para garantir, por exemplo, que o
diretório de saída exista, mas mudanças na data do diretório não provocam uma
nova compilação.

Nas regras do projeto:

- `%` representa o nome variável do programa ou arquivo;
- `$@` representa o alvo que está sendo produzido;
- `$<` representa a primeira dependência;
- regras como `%.pipeline.hex` permitem aplicar o mesmo fluxo a Dhrystone,
  CoreMark, Raystones e programas de teste.

## Compilação dos objetos comuns

Os arquivos em `benchmarks/common` formam o pequeno suporte de execução
compartilhado por todos os programas. As regras genéricas compilam fontes C com
o GCC e fontes Assembly com o assembler:

```{literalinclude} ../../benchmarks/common.mk
:language: make
:caption: Regras para objetos C e Assembly
:lines: 27-31
```

Os arquivos resultantes são armazenados em `build/obj`. Entre eles estão as
rotinas de impressão, `memcpy`, acesso aos contadores de desempenho e o código
de inicialização.

As fontes C são compiladas com otimização `-O2`, sem código independente de
posição e sem mecanismos que dependam de um sistema operacional, como proteção
de pilha. As fontes Assembly habilitam `Zicsr`, necessária para ler os
contadores `cycle` e `instret`.

## Compilação do benchmark

Dhrystone e CoreMark são formados por vários arquivos C. O GCC compila e combina
as fontes de cada um em um único objeto relocável usando `-r`:

```text
build/obj/dhrystone.o
build/obj/coremark.o
```

Raystones possui uma única fonte principal e gera diretamente
`build/obj/raystones.o`. Essa etapa ainda não produz um programa executável: os
endereços definitivos e as referências às rotinas comuns são resolvidos no
link final.

## Construção do ELF

A regra abaixo liga o objeto do benchmark ao código de inicialização, aos
objetos comuns, à `libm` e à `libgcc`:

```{literalinclude} ../../benchmarks/Makefile
:language: make
:caption: Ligação e geração da listagem
:lines: 46-48
```

O linker recebe o formato `elf32lriscv`, o linker script do projeto e
`-nostdlib`. Assim, nenhuma inicialização, chamada de sistema ou biblioteca C do
host é adicionada implicitamente. A `libgcc` ainda fornece operações auxiliares
geradas pelo compilador — por exemplo, divisões ou operações de ponto flutuante
que não existem diretamente em RV32I — e a `libm` atende às operações
matemáticas usadas pelos programas.

O resultado principal é:

```text
build/<benchmark>.pipeline.elf
```

Em seguida, `objdump` gera `<benchmark>.pipeline.elf.list`, contendo a
desmontagem do programa. Essa listagem é útil para relacionar os endereços
executados às instruções RISC-V produzidas pelo compilador.

## Separação das memórias

O ELF contém código e dados no mesmo arquivo, mas o SoC possui imagens distintas
para ROM de programa e RAM de dados. A separação não é realizada pelo GCC: ela
é feita pelo `objcopy`, que faz parte da mesma GNU toolchain.

```{literalinclude} ../../benchmarks/Makefile
:language: make
:caption: Geração das imagens de programa e dados
:lines: 34-44
```

Para a memória de programa, `objcopy` seleciona somente a seção `.text`. Para a
memória de dados, seleciona `.data` e subtrai `0x10000` dos endereços, fazendo o
primeiro byte da RAM corresponder à posição zero do arquivo.

As opções restantes produzem arquivos no formato Verilog, organizados em
palavras de quatro bytes, preenchendo regiões ausentes com zero até o limite de
64 KiB. Os artefatos consumidos pela simulação são:

```text
build/hex/<benchmark>.PROGROM.hex
build/hex/<benchmark>.DATARAM.hex
```

O arquivo `build/<benchmark>.pipeline.hex` funciona apenas como um marcador de
que as duas imagens foram geradas. O Make usa as dependências e datas de
modificação para reconstruir somente os artefatos ausentes ou desatualizados.

## Resumo do fluxo

Em ordem, a construção realiza:

1. criação dos diretórios de saída;
2. compilação das fontes comuns e do benchmark em objetos;
3. ligação dos objetos em um ELF bare-metal;
4. geração da listagem de instruções;
5. extração da ROM e da RAM em arquivos hexadecimal;
6. criação do marcador usado pelas regras de simulação.
