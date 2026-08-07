# Linker script e mapa de memória

O compilador gera objetos com seções como `.text`, `.data`, `.rodata` e `.bss`,
mas ainda sem os endereços finais esperados pelo processador. O linker script
define onde cada seção será colocada e garante que o ELF corresponda ao mapa de
memória implementado pelo SoC.

O script utilizado pelo projeto é:

```{literalinclude} ../../benchmarks/common/pipeline.ld
:language: text
:caption: benchmarks/common/pipeline.ld
:linenos:
```

## Regiões físicas

O mapa é dividido em duas regiões de 64 KiB:

- **`PROGROM`:** começa em `0x00000000`, permite leitura e execução e armazena
  as instruções;

- **`DATARAM`:** começa em `0x00010000`, permite leitura e escrita e armazena
  dados e a pilha.

O endereço `0x00020000`, imediatamente após a RAM, é usado como valor inicial do
ponteiro de pilha. Como a pilha cresce para endereços menores, seu primeiro uso
ocorre dentro de `DATARAM`.

A região de E/S, iniciada em `0x00400000`, não aparece no linker script porque
não armazena seções do programa. Ela é acessada explicitamente por endereços
*memory-mapped*.

## Organização das seções

A seção de saída `.text` recebe todo o código e é alinhada em quatro bytes antes
de ser colocada em `PROGROM`.

A seção de saída `.data` concentra todo o conteúdo que deve existir na RAM:

- dados inicializados, encontrados em `.data` e `.sdata`;
- constantes de `.rodata` e `.srodata`;
- dados inicialmente zerados de `.bss`, `.sbss` e `COMMON`;
- seções auxiliares que eventualmente sejam emitidas pelo compilador.

Reunir esses conteúdos em uma única seção é uma decisão do ambiente: o
`objcopy` precisa produzir apenas uma imagem `DATARAM.hex`, e essa imagem é
carregada diretamente na RAM antes do primeiro ciclo do programa. Por isso, o
código de inicialização não precisa copiar `.data` da ROM nem limpar `.bss`.

Essa organização é diferente de sistemas que armazenam os valores iniciais da
RAM dentro da ROM e realizam a cópia durante o boot. No TRYonRISCV, ROM e RAM já
recebem arquivos independentes.

## Ponto de entrada

O objeto `start_pipeline_asm.o` é colocado antes dos demais objetos no comando
de ligação. Dessa forma, o símbolo `start` ocupa o início de `.text`, no endereço
`0x00000000`, que também é o primeiro endereço buscado pelo processador.

O script não cria heap nem reserva uma área fixa para a pilha. O limite prático
entre dados estáticos e pilha é responsabilidade do programa e deve permanecer
dentro dos 64 KiB de `DATARAM`.
