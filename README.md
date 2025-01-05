
# PROJETO RISCV ([IC/FAPESP](https://bv.fapesp.br/pt/bolsas/216904/risc-v-superescalar-com-despacho-duplo-para-fpgas/))

O projeto é desenvolvido em duas frentes: [SIMULAÇÃO](SIM/README.md) e [SÍNTESE](RTL/README.md).

## IMPLEMENTAÇÕES

O alvo central do desenvolvimento são processadores que seguem o padrão RV32I, ou seja, a arquitetura RISC-V com 32bits e operações com números inteiros. Além disso, tratando-se da organização interna, a base dos processadores foi feita através de um pipeline com 5 estágios: Instruction Fetch, Instruction Decode, Execute, Memory Access e Write Back. Partindo de uma ideia modular, é possível configurar as características desejadas através dos parâmetros do processador. Para tal foi criado o arquivo SoC, que permite a utilização do processador de maneira a isolar o processador de características externas, como memórias, uart, IO, etc.

### BYPASS

É sabido que um processador pipeline básico possui algum tipo de Hazard, a chave central, portanto, do desenvolvimento de uma organização ótima é como lidar com estes problemas. Além disso, fica claro, com rasas pesquisas, que existem diversas maneiras de resolver tais problemas. Logo, primeiramente parece ser natural mapea-los de maneira crua, para só então montar possíveis soluções.

Um dos principais Hazards é o de dados, que de forma resumida, trata do uso de dados que ainda não foram devidamente armazenados em seus respectivos registros. Analisando a arquitetura utilizada é possível chegar a conclusão de que dados podem ser obtidos através de duas fontes, o banco de registratodres e os valores imediatos. Contudo, estas possuem uma crucial diferença, já que os valores imediatos estão nos 32 bits da instrução, ou seja, podem ser acessados em qualquer lugar com os registradores de pipeline, que mantém o dado intacto; em contrapartida, o banco de registradores só pode ser acessado uma vez por ciclo, ou seja, só é feita uma escrita por ciclo no último estágio, Write Back, logo, cria-se uma dependência entre acessar e escrever dados no banco de registradores, traduzindo: cada instrução leva 2 ciclos para buscar e 5 para escrever. Portanto, existem duas alternativas claras: esperar 1-3 ciclos, caso apareça alguma dependência, ou escrever a cada ciclo, reduzindo a espera.

A alternativa de esperar é implementada de maneira que, a cada instrução que chega no estágio de decodificação é analisada sua relação com o banco de registradores, se ela utilizará um, ou dois, registradores que estão sendo manipulados nos estágios posteriores (Execute, Memory Acess ou Write-Back), então é necessária uma pausa nos estágios de Fetch e Decode até que a manipulação citada termine, além disso, o estágio de Execute é alimentado com a instrução NOP. 

Porém, neste caso o dado do registrador em questão fica pronto antes de ser utilizado (no estágio Execute ou no Memory Acess), ou seja, os estágios de Fetch e Decode ficam esperando um dado que já está pronto, mas não está presente no banco de registrador. Logo, se no fim de cada estágio de Execute ou Memory Acess ser feita uma escrita no banco de registradores essa dependência diminui. De maneira geral, um Hazard de dado é transformado em um Hazard estrutural já que não é possivel escrever em dois registradores em um único ciclo. Portanto, uma nova dependência aparece quando duas instruções, que escrevem no banco de registradores, estão presentes nos estágios Execute e Memory Acess. Analisando o conjunto de instruções do padrão RV32I é possível dividir as operações de escrita no banco conforme dados obtidos através da ULA ou da memória de dados. Os primeiros são todas as intruções além de Stores, Branchs, Loads e Ecalls; e os seguintes são Loads e Ecalls. Com essa divisão feita, é possível observar que o Hazard estrutural, de duas escritas no banco de registradores, acontece apenas quando duas instruções que, respecivamente, escrevem no estágio de Execute e no estágio de Memory Acess aparecem no pipeline. A solução de tal hazard é feita simplemesmente atrasando a instrução mais recente no pipeline em um ciclo, quando ela chega no estágio de Decode.



### MÓDULOS

 - O processador mais básisco, sem nenhum módulo, apenas lida com os Hazards de Controle e Dados através de Stalls e Flushes.
 - O módulo BYPASS permite o uso de adiantamento dos dados evitando Stalls no estágio Execute.
 - O módulo BRANCH_PRED=1 trás o uso da técnica BTFNT(Backwards Taken, Forwards Not Taken), além disso, todos os módulos de branch prediction também já lidam com JAL, eliminando um dos hazards de controle.
 - O módulo BRANCH_PRED=2 usa um método dinâmico com uma tabela do histórico de desvios, tendo cada posição dois bits de armazenamento configurados por um somador saturado.
 - O módulo BRANCH_PRED=3 melhora a busca na tabela anterior através de indexação pela estratégia GSELECT.
 - O módulo BRANCH_PRED=4 apenas muda a indexação para GSHARE.
