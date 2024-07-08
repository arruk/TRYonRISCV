
# PROJETO RISCV ([IC/FAPESP](https://bv.fapesp.br/pt/bolsas/216904/risc-v-superescalar-com-despacho-duplo-para-fpgas/))

## DEPENDÊNCIAS

- [RISCV Toolchain (riscv64-unknow-ef)](https://github.com/sifive/freedom-tools/releases): export RV_UNK=(caminho_da_toolchain)
- Verilator: `apt-get install verilator`;
- [Yosys](https://github.com/YosysHQ/yosys);
- [Next-PNR](https://github.com/YosysHQ/apicula): para dispositivos GOWIN;


## SIMULAÇÃO

Ao acessar o diretório [SIM](SIM) estarão disponíveis as implementações dos processadores, nomeados de core(version).v. Além disso, os programas que geram os arquivos de DATARAM (Memória de Dados) e PROGROM (Memória de Programa) estão localizaods no diretório [SIM/FIMWARE](SIM/FIRMWARE).

Para gerar ambos arquivos de memória, com respectivamente 64kB ou 32kB de espaço, é necessário usar um dos comandos:

	make (programa_alvo).pipeline.hex, ou make (programa_alvo).small.pipeline.hex

sendo "programa_alvo" o programa a ser executado no processador. Feito isso e voltando ao diretório SIM, é possivel encontrar dois 
arquivos .hex que estão formatados da maneira que o leitor de arquivos do Verilog consegue entender. Por fim, para executar o programa é
necessário usar o script run_verilator.sh, que possui algumas opções:
	
	./run_verilator (implementacao_alvo).v (opção).

Para simular de maneira a apenas exibir a saída padrão use opção = "v" e para executar todos os Benchmarks use opção = "a". Caso o programa alvo seja algum Benchmark(CoreMark, Dhrystones ou Raystones) as informações de CPI e desempenho serão adicionadas a uma nova linha no arquivo do respectivo Benchmark no diretorio [INFO/BENCH](INFO/BENCH).

## SÍNTESE

A síntese dos códigos pode ser feita apenas para os dispositivos TangNano9k e SipeedPrimer20k. A síntese para qualquer um dos dois dispositivos será feita com as memórias reduzidas a 32kB de espaço de armazenamento. Por fim, para realizar a síntese é preciso usar o script:
	
	BOARDS/run_(board) (implementacao_alvo).v

sendo board o FPGA a ser utilizado(nano9k ou primer20k). O resumo da sintese será direcionado para o diretorio [INFO/BOARDS](INFO/BOARDS)/(implementacao_alvo).txt.

## IMPLEMENTAÇÕES

O alvo central do desenvolvimento são processadores que seguem o padrão RV32I, ou seja, a arquitetura RISC-V com 32bits e operações com números inteiros. Além disso, tratando-se da organização interna, a base dos processadores foi feita através de um pipeline com 5 estágios: Instruction Fetch, Instruction Decode, Execute, Memory Access e Write Back. Partindo de uma ideia modular, é possível configurar as características desejadas através dos parâmetros do processador. Para tal foi criado o arquivo SoC, que permite a utilização do processador de maneira a isolar o processador de características externas, como memórias, uart, IO, etc.

### MÓDULOS

 - O processador mais básisco, sem nenhum módulo, apenas lida com os Hazards de Controle e Dados através de Stalls e Flushes.
 - O módulo BYPASS permite o uso de adiantamento dos dados evitando Stalls no estágio Execute.
 - O módulo BRANCH_PRED=1 trás o uso da técnica FTBNT(Forward Taken, Backwards Not Taken), além disso, todos os módulos de branch prediction também já lidam com JAL, eliminando um dos hazards de controle.
 - O módulo BRANCH_PRED=2 usa um método dinâmico com uma tabela do histórico de desvios, tendo cada posição dois bits de armazenamento configurados por um somador saturado.
 - O módulo BRANCH_PRED=3 melhora a busca na tabela anterior através de indexação pela estratégia GSELECT.
 - O módulo BRANCH_PRED=4 apenas muda a indexação para GSHARE.
