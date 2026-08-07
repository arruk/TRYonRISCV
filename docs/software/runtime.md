# Ambiente de execução bare-metal

Em um sistema Linux, um programa C normalmente recebe do sistema operacional e
da biblioteca C todo o suporte necessário para começar e terminar sua execução.
No TRYonRISCV não há sistema operacional: após o reset, o processador começa a
buscar instruções diretamente no endereço zero.

Por isso, o repositório fornece um ambiente mínimo com três responsabilidades:

- preparar os registradores necessários antes de chamar `main`;
- oferecer pequenas rotinas que substituem partes da biblioteca C;
- traduzir a saída de caracteres em acessos aos periféricos do SoC.

## Código de inicialização

O *C runtime* tradicional possui um arquivo chamado `crt0`. Ele configura a
pilha, inicializa dados globais, executa construtores, chama `main` e encaminha o
valor retornado para o sistema operacional.

Neste projeto, `start_pipeline.S` desempenha uma versão mínima desse papel:

```{literalinclude} ../../benchmarks/common/start_pipeline.S
:language: asm
:caption: benchmarks/common/start_pipeline.S
:linenos:
```

A sequência ativa realiza quatro operações:

1. carrega `0x00400000` em `gp`, usando-o como base da região de E/S;
2. posiciona `sp` em `0x00020000`, no topo da RAM;
3. chama a função C `main`;
4. executa `EBREAK` quando `main` retorna.

Na simulação, `EBREAK` ativa o sinal de término observado pelo testbench. Não há
retorno para um sistema operacional.

O código também não copia `.data` nem limpa `.bss`, pois esses conteúdos já
estão presentes em `DATARAM.hex`. Argumentos de linha de comando, construtores
C++, heap e rotinas de finalização não fazem parte deste ambiente mínimo.

## Por que implementar funções básicas

O link utiliza `-nostdlib`, portanto não existe uma libc responsável por
`printf`, `puts`, `memcpy` ou pelo tratamento de chamadas de sistema. Mesmo que
uma libc completa fosse ligada, suas funções de E/S esperariam uma interface de
sistema operacional que não existe no SoC.

O diretório `benchmarks/common` fornece apenas o necessário para os programas
atuais:

- `print.c` implementa versões reduzidas de `printf`, `puts` e conversão de
  números;
- `memcpy.c` fornece a cópia de blocos usada pelo código compilado;
- `errno.c` satisfaz referências a `errno`;
- `perf.S` lê os contadores de ciclos e instruções aposentadas;
- `putchar.S` implementa a operação básica de saída.

O `printf` reduzido entende somente os formatos necessários aos benchmarks e
envia cada caractere para `putchar`.

## Implementação de `putchar`

Sem chamadas de sistema, imprimir um caractere significa escrever diretamente
no periférico UART mapeado em memória. A implementação é curta o suficiente
para ser escrita em Assembly:

```{literalinclude} ../../benchmarks/common/putchar.S
:language: text
:caption: benchmarks/common/putchar.S
:linenos:
```

Pela convenção de chamadas RISC-V, o caractere chega em `a0`. A função usa o
valor de `gp`, preparado pelo código de inicialização, e executa os seguintes
passos:

1. escreve o caractere no registrador `IO_UART_DAT`, em `0x00400008`;
2. lê o registrador de controle `IO_UART_CNTL`, em `0x00400010`;
3. testa o bit 9, que indica que a UART ainda está ocupada;
4. aguarda esse bit voltar a zero e retorna ao chamador.

No FPGA, essa escrita alimenta o transmissor serial. Durante a simulação, o SoC
intercepta a mesma escrita e usa `$write` para mostrar o caractere no terminal.
Assim, o programa executa a mesma interface de E/S nos dois ambientes.
