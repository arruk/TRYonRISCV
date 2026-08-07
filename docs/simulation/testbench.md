# Testbench em C++

O testbench é a ligação entre o modelo C++ gerado pelo Verilator e o monitor de
benchmarks. Sua responsabilidade é conduzir o clock, avaliar o SoC, observar os
sinais de instrumentação e encerrar a execução quando o processador indicar
`halt`.

O código utilizado na simulação é apresentado diretamente do arquivo do
repositório, evitando que esta página fique desatualizada em relação à
implementação:

```{literalinclude} ../../sim/bench.cpp
:language: cpp
:caption: sim/bench.cpp
:linenos:
```

## Inicialização

A função `Verilated::commandArgs` registra os argumentos da linha de comando e
permite que os módulos SystemVerilog consultem `PROGROM` e `DATARAM`. Em seguida,
o objeto `VSOC` instancia o modelo cujo módulo de topo é `SOC`.

A função auxiliar `getPlusArg` procura argumentos no formato `+NOME=valor`. Ela
é usada pelo C++ para obter:

- as máscaras de pipelines ativos e de predição;
- o caminho do arquivo de resultados;
- os nomes do core e do benchmark;
- as definições usadas na construção;
- a opção que habilita a gravação do CSV.

Se algum argumento obrigatório estiver ausente, a função lança uma exceção com
o nome do valor esperado.

## Laço de simulação

Cada passagem pelo laço principal representa um ciclo completo de clock:

1. `CLK` é colocado em nível alto e `top.eval()` propaga a borda de subida;
2. o monitor amostra desvios, acertos de predição, `JAL` e `JALR`;
3. o sinal `bench_halt` é verificado;
4. se a execução continuar, `CLK` volta ao nível baixo e o modelo é avaliado
   novamente.

O laço também observa `Verilated::gotFinish()`, permitindo que uma finalização
solicitada pelo RTL encerre a simulação.

## Monitoramento dos resultados

O `BenchMonitor` mantém contadores separados para os pipelines A e B. Os sinais
recebidos do SoC são máscaras de bits: o bit zero representa A e o bit um
representa B. As máscaras `ACTIVE_PIPELINES` e `PREDICTION_MASK`, calculadas
pelo Makefile, impedem que sinais inexistentes sejam contabilizados para um
determinado core.

Quando `bench_halt` é ativado, o testbench consulta os contadores de ciclos e de
instruções aposentadas fornecidos pelo processador. Se `SAVE=1`, chama
`write_csv`, que acrescenta uma linha por pipeline ativo contendo:

- core e benchmark;
- pipeline;
- desvios e acertos de predição;
- quantidades de `JAL` e `JALR`;
- ciclos e instruções aposentadas;
- opções utilizadas na construção do simulador.

A coleta fica fora do RTL principal para evitar a repetição da mesma lógica em
cada processador e facilitar mudanças no formato dos resultados.
