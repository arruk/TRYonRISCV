# Comandos e configurações

Os comandos de simulação devem ser executados no diretório `sim`. Antes disso,
carregue o ambiente do projeto para disponibilizar a toolchain RISC-V:

```bash
source env.sh
cd sim
```

Para consultar os cores, benchmarks e opções reconhecidos pelo Makefile, use:

```bash
make help
```

## Execução padrão

O comando mais simples é:

```bash
make
```

Sem argumentos, ele constrói o simulador para o `torvs7C`, prepara o Dhrystone
e executa o programa. Esse comportamento equivale a usar:

```bash
make CORE=torvs7C BENCHMARK=dhrystone SAVE=0
```

Os resultados são exibidos pelo próprio benchmark. As métricas do monitor só
são acrescentadas ao CSV quando `SAVE=1`.

## Escolha do core e do benchmark

Use `CORE` para selecionar uma implementação TORV ou TORVS e `BENCHMARK` para
selecionar o programa:

```bash
make CORE=torv6 BENCHMARK=coremark
make CORE=torvs9C BENCHMARK=raystones SAVE=1
```

Os benchmarks disponíveis atualmente são `dhrystone`, `coremark` e
`raystones`. A lista de cores é obtida diretamente dos arquivos em
`rtl/cores/torv` e `rtl/cores/torvs` e pode ser consultada com `make help`.

## Configurações do TORVS

Os cores TORVS permitem ampliar as operações aceitas pelo pipeline B:

- **`STORE_B=1`:** habilita instruções de armazenamento em B.

- **`LOAD_B=1`:** habilita cargas e armazenamentos em B.

- **`BRANCH_B=1`:** habilita desvios condicionais, `JAL`, `JALR`, cargas e
  armazenamentos em B.

- **`RAS=1`:** habilita a pilha de endereços de retorno.

As opções são cumulativas: `LOAD_B` implica `STORE_B`, enquanto `BRANCH_B`
implica `LOAD_B` e `STORE_B`. Elas podem ser combinadas no mesmo comando:

```bash
make CORE=torvs7C LOAD_B=1
make CORE=torvs9C BRANCH_B=1 RAS=1 BENCHMARK=coremark SAVE=1
```

Esses recursos são definidos durante a construção do simulador. Depois de
alterar `CORE`, `STORE_B`, `LOAD_B`, `BRANCH_B` ou `RAS`, execute `make` ou
`make build` antes de usar somente `make run`.

## Regras disponíveis

- **`make` ou `make all`:** constrói o executável e realiza uma simulação.

- **`make build`:** executa o Verilator e compila o executável, sem iniciar o
  benchmark.

- **`make run`:** prepara o benchmark, caso necessário, e executa um simulador
  já construído.

- **`make benchmark`:** solicita apenas a preparação das imagens de memória do
  benchmark selecionado.

- **`make print`:** apresenta `results/results.csv` como uma tabela no terminal.
  Essa regra requer o comando `mlr`, fornecido pelo Miller.

- **`make clean`:** remove os executáveis gerados em `sim/build`. Os benchmarks
  e o arquivo de resultados não são removidos.

Também existem regras para processar vários cores:

- `make all-torv`, `make all-torvs` e `make all-cores` constroem e executam cada
  core da família selecionada;
- `make build-all-torv` e `make build-all-torvs` apenas constroem os
  executáveis.

Para salvar as métricas de todas as execuções em lote, acrescente `SAVE=1`:

```bash
make all-cores BENCHMARK=dhrystone SAVE=1
```
