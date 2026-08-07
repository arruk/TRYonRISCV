# TORVS: pipeline superescalar

A família TORVS explora a execução em ordem de até duas instruções por ciclo.
Para isso, busca duas instruções consecutivas e tenta distribuí-las entre os
pipelines A e B. O pipeline A aceita o fluxo completo de instruções, enquanto o
pipeline B pode receber a segunda instrução quando o tipo da operação e suas
dependências permitem a emissão em paralelo.

Os dois pipelines possuem caminhos de encaminhamento entre si. Ainda assim, o
despacho é conservador: instruções dependentes não são emitidas juntas, e uma
operação não suportada pelo pipeline B é preservada para o ciclo seguinte. O
objetivo é aumentar o paralelismo sem alterar a ordem observável do programa.

## Cores disponíveis

As variantes atuais compartilham a mesma organização superescalar e diferem
principalmente no mecanismo usado para antecipar mudanças do fluxo de controle.

- **`torvs5C` — sem predição de desvios condicionais:** serve como referência
  para medir o ganho dos preditores. Um desvio tomado é corrigido quando sua
  condição é resolvida.

- **`torvs7C` — predição BTFNT estática:** prevê desvios para trás como tomados e
  desvios para frente como não tomados, sem utilizar uma tabela de histórico.

- **`torvs9C` — predição GShare dinâmica:** utiliza contadores saturantes de dois
  bits e combina o endereço do desvio com o histórico global, adaptando-se ao
  comportamento observado durante a execução.

Saltos diretos com `JAL` são encaminhados antecipadamente em todas as três
versões. A pilha de endereços de retorno pode ser habilitada separadamente para
antecipar destinos de retornos realizados com `JALR`.

## Configuração do pipeline B

As capacidades do pipeline B são selecionadas na compilação da simulação por
variáveis do Makefile. Sem opções adicionais, ele recebe operações aritméticas,
lógicas, `LUI` e `AUIPC`.

- **`STORE_B=1`:** permite instruções de `STORE` no pipeline B.

- **`LOAD_B=1`:** permite `LOADS` no pipeline B e habilita também `STORE_B`.

- **`BRANCH_B=1`:** permite desvios condicionais, `JAL` e `JALR` no pipeline B;
  habilita também `LOADS` e `STORES`.

- **`RAS=1`:** habilita uma pilha de quatro endereços para predição de retornos
  de função.

As dependências entre as opções refletem os recursos necessários pelo caminho
B: `LOAD_B` implica `STORE_B`, enquanto `BRANCH_B` implica ambos. Quando os
desvios são habilitados em B, o preditor do `torvs7C` ou do `torvs9C` também é
aplicado a esse pipeline. No `torvs5C`, os desvios continuam sem predição.

Exemplos de configuração:

```bash
cd sim

# Configuração básica do pipeline B
make CORE=torvs5C

# Adiciona `LOADS` e `STORES` ao pipeline B
make CORE=torvs7C LOAD_B=1

# Habilita todas as classes previstas para B e a predição de retornos
make CORE=torvs9C BRANCH_B=1 RAS=1
```

Cada combinação produz uma implementação diferente. Comparações de desempenho
devem registrar o core e as opções utilizadas, pois ampliar o pipeline B pode
reduzir o número de ciclos, mas também aumenta o caminho lógico e os recursos de
hardware necessários.
