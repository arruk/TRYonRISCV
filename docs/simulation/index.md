# Simulação

O fluxo de simulação utiliza o Verilator para transformar o SoC e o processador
selecionado em um executável C++. O mesmo ambiente permite trocar o core, o
benchmark e os recursos opcionais do TORVS sem editar diretamente o comando do
Verilator.

Esta seção está organizada do uso mais comum para os detalhes internos:

1. comandos e configurações disponíveis no Makefile;
2. etapas realizadas para construir e executar a simulação;
3. funcionamento geral do testbench escrito em C++.

```{toctree}
:maxdepth: 2
:caption: Simulação

commands
verilator
testbench
```
