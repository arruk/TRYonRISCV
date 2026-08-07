# TORV: pipeline escalar

A família TORV contém processadores RV32I escalares, com emissão e aposentadoria
em ordem de uma instrução por ciclo. O caminho de execução é organizado em cinco
estágios: busca, decodificação, execução, acesso à memória e escrita no banco de
registradores.

As versões representam uma evolução incremental da mesma arquitetura. O foco
está no tratamento de dependências de dados e na redução do custo causado por
desvios, mantendo uma estrutura simples para estudo e comparação.

## Evolução das versões

- **`torv1` — implementação de referência:** dependências entre instruções são
  resolvidas principalmente com esperas no pipeline e não há predição de
  desvios.

- **`torv2` — encaminhamento de resultados:** adiciona *forwarding* para reduzir
  as esperas. Dependências imediatamente após cargas ainda exigem uma bolha.

- **`torv3` — predição estática:** utiliza BTFNT, prevendo desvios para trás como
  tomados e desvios para frente como não tomados.

- **`torv4` — predição bimodal:** utiliza contadores saturantes de dois bits,
  indexados pelo endereço da instrução.

- **`torv5` — predição GShare:** combina o endereço do desvio com o histórico
  global para distinguir melhor padrões de execução.

- **`torv6` — predição de retornos:** acrescenta uma pilha de endereços de
  retorno ao GShare, antecipando retornos de função realizados com `JALR`.

Os cores `torv2p1` e `torv4p1` são variações experimentais que antecipam parte
da decisão de encaminhamento para avaliar outra divisão do caminho lógico entre
os estágios. O `torv5p1` é atualmente equivalente ao `torv5` e permanece no
repositório como referência histórica.

## Execução e controle

Todos os cores executam programas bare-metal compilados para `rv32i/ilp32` e
expõem interfaces separadas para instruções, dados e E/S ao SoC. O hardware
também fornece os contadores de ciclos e instruções aposentadas utilizados nos
benchmarks. No ambiente de simulação, uma instrução de parada encerra a execução
e entrega essas métricas ao monitor.

Quanto mais recente a versão, maior a quantidade de estado dedicada à predição.
Por isso, a comparação entre cores deve considerar em conjunto desempenho,
frequência de síntese e utilização de recursos, e não somente o número de
ciclos de um benchmark.
