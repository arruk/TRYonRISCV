# Benchmarks disponíveis

Os benchmarks exercitam perfis de execução diferentes, permitindo comparar os
cores sem depender de um único tipo de programa. Todos são adaptados para o
ambiente bare-metal e usam os contadores `cycle` e `instret` do processador.

## Dhrystone

Dhrystone 2.1 é um benchmark sintético de processamento inteiro. Ele exercita
chamadas de funções, manipulação de estruturas, ponteiros, strings, atribuições
e desvios, tentando representar operações comuns em programas de sistema.

A versão do repositório executa 50.000 iterações e substitui as poucas
dependências dinâmicas do programa original por estruturas previamente
alocadas. Ao final, verifica valores conhecidos e apresenta ciclos, instruções
aposentadas, CPI, Dhrystones por segundo por MHz e DMIPS por MHz.

Ele é útil como primeiro teste por ter execução determinística e utilizar
principalmente operações inteiras da ISA RV32I.

## CoreMark

CoreMark combina três cargas principais: operações sobre listas encadeadas,
cálculos com matrizes e uma máquina de estados que processa sequências de
caracteres. Códigos CRC verificam se a execução produziu os resultados
esperados.

A configuração atual utiliza 300 iterações e memória alocada na pilha. O port
do projeto mede o tempo pelos contadores do processador e apresenta, entre
outras informações, CoreMark por MHz e CPI.

Em comparação com Dhrystone, CoreMark oferece uma carga mais variada e inclui
uma verificação padronizada dos resultados intermediários.

## Raystones

Raystones é um pequeno *ray tracer* derivado do TinyRayTracer. Ele calcula a
interseção de raios com esferas e aplica iluminação, sombras, reflexões e
refrações. Isso produz uma carga com aritmética mais intensa e grande quantidade
de chamadas de funções.

Como o alvo é RV32I, operações de ponto flutuante são implementadas em software
pelas rotinas fornecidas pela toolchain. Dessa forma, o benchmark também expõe o
custo dessas operações em um processador sem extensão de ponto flutuante.

A execução de medição renderiza uma imagem de 40 por 20 pixels sem enviar o
conteúdo gráfico ao terminal, evitando incluir o custo de impressão na região
medida. O resultado informa CPI e a métrica Raystones calculada a partir do
número de pixels e ciclos.
