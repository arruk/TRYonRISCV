# Introdução ao TRYonRISCV

O TRYonRISCV é um ambiente para estudo e experimentação de processadores RISC-V, abrangendo desde a descrição do hardware até a execução de programas bare metal. O projeto busca tornar mais acessível a
observação das diferentes etapas envolvidas na construção e utilização de um processador.

O repositório contém implementações próprias em Verilog e SystemVerilog, incluindo processadores escalares da família TORV e versões superescalares da família TORVS. Essas implementações permitem explorar
diferentes organizações de pipeline, mecanismos de predição de desvios e distribuição de instruções entre unidades de execução.

O fluxo de software permite compilar benchmarks e programas em C para RISC-V, gerando as imagens utilizadas pelas memórias de instruções e dados do hardware. Como a execução ocorre sem sistema operacional, o
próprio projeto fornece os arquivos de inicialização, scripts de ligação e demais componentes necessários para formar um ambiente bare metal completo.

Os processadores podem ser avaliados por simulação com Verilator, incluindo a coleta de métricas de execução, ou sintetizados para placas FPGA. Dessa forma, o mesmo programa pode ser acompanhado desde sua
compilação até sua execução em um modelo simulado ou em hardware físico.

Mais do que disponibilizar processadores isolados, o TRYonRISCV procura oferecer um ecossistema integrado no qual software, ferramentas de simulação e hardware são desenvolvidos e avaliados em conjunto. Isso
permite compreender melhor como um programa compilado interage com uma arquitetura criada dentro do próprio projeto.


```{toctree}
:maxdepth: 2
:caption: Introdução ao TRYonRISCV

initial-setup
```
