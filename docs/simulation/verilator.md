# Fluxo da simulação

O comando `make` executa duas etapas principais: `build`, responsável pela
construção do simulador, e `run`, responsável por preparar o programa e iniciar
a execução. A separação permite reconstruir o hardware e repetir benchmarks de
forma independente.

## Seleção da implementação

O nome informado em `CORE` determina automaticamente a família e o arquivo RTL:

- nomes iniciados por `torv` usam uma implementação em `rtl/cores/torv` e as
  configurações de `sim/configs/torv.mk`;
- nomes iniciados por `torvs` usam uma implementação em `rtl/cores/torvs` e as
  configurações de `sim/configs/torvs.mk`.

O arquivo de configuração informa quantos pipelines devem ser monitorados, em
quais deles existe predição e quais definições opcionais serão enviadas ao
Verilator.

## Construção com o Verilator

A regra `build` cria `sim/build/<core>/obj_dir` e executa o Verilator com:

- `SOC` como módulo de topo;
- o SoC, as memórias, os módulos comuns e o core escolhido como fontes RTL;
- `bench.cpp` e `bench_monitor.cpp` como fontes C++;
- `BENCH`, a família do core e as opções do TORVS como definições de compilação;
- `--cc --exe` para gerar o modelo C++ e vinculá-lo ao testbench.

De forma simplificada, o comando gerado possui esta estrutura:

```bash
verilator -D<familia> -DBENCH -D<opcoes> \
  --Mdir build/<core>/obj_dir \
  --top-module SOC --cc --exe \
  bench.cpp bench_monitor.cpp <fontes-rtl>
```

O Verilator produz, entre outros arquivos, o Makefile `VSOC.mk`. A regra chama
esse Makefile para compilar o modelo e gerar o executável:

```text
sim/build/<core>/obj_dir/VSOC
```

Cada core possui seu próprio diretório de saída. Entretanto, configurações
diferentes de um mesmo core compartilham esse diretório; por isso, é necessário
reconstruí-lo ao alterar opções como `LOAD_B` ou `RAS`.

## Localização e preparação do benchmark

O nome fornecido em `BENCHMARK` é usado para formar os caminhos:

```text
benchmarks/build/hex/<benchmark>.PROGROM.hex
benchmarks/build/hex/<benchmark>.DATARAM.hex
```

Antes da execução, a regra `benchmark` chama o Makefile do diretório
`benchmarks` e solicita o alvo `<benchmark>.pipeline.hex`. O Make verifica as
dependências: se as imagens não existirem ou estiverem desatualizadas, elas são
geradas; caso contrário, os arquivos existentes são reutilizados.

`PROGROM.hex` contém as instruções que inicializam a ROM, enquanto
`DATARAM.hex` contém os dados iniciais da RAM. A transformação do programa em
ELF e em imagens hexadecimal é detalhada na seção de
[software](../software/compilation.md).

## Execução e carregamento da memória

A regra `run` cria o diretório de resultados e inicia `VSOC`. Os caminhos das
memórias e os dados da configuração são enviados como *plusargs*:

```bash
VSOC \
  +PROGROM=<caminho.PROGROM.hex> \
  +DATARAM=<caminho.DATARAM.hex> \
  +CORE=<core> +BENCHMARK=<benchmark> \
  +RESULTS=<caminho-results.csv> +SAVE=<0-ou-1> \
  +ACTIVE_PIPELINES=<mascara> +PREDICTION_MASK=<mascara> \
  +DEFINES=<opcoes>
```

Durante a inicialização, os módulos de memória obtêm `PROGROM` e `DATARAM` com
`$value$plusargs` e carregam os arquivos usando `$readmemh`. A simulação é
encerrada com uma mensagem de erro se algum desses caminhos não for informado.
Assim, os arquivos hexadecimal podem permanecer fora do diretório do
executável e nenhum caminho absoluto precisa ser gravado no RTL.

Os demais argumentos são consumidos pelo testbench para configurar a coleta de
métricas e identificar a execução. Quando `SAVE=1`, os resultados são
acrescentados a `sim/results/results.csv`; quando o arquivo ainda não existe, o
monitor também escreve o cabeçalho.
