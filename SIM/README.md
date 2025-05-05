# SIMULAÇÃO

## DEPENDÊNCIAS

- [RISCV Toolchain (riscv64-unknow-ef)](https://github.com/sifive/freedom-tools/releases) (preferivelmente v8.3.0)
	- export RV\_UNK=(caminho\_da\_toolchain)
- Verilator: `apt install verilator` ou `dnf install verilator`;
- G++: `apt install g++` ou `dnf install gcc-c++`

## COMEÇANDO

Ao acessar os diretórios [CORE](CORE), [COPROC](COPROC) ou
[TORVS](TORVS) estarão disponíveis as implementações dos processadores.
Além disso, os programas que geram os arquivos de DATARAM (Memória de Dados) e
PROGROM (Memória de Programa) estão localizaods no diretório [FIMWARE](FIRMWARE).

Para gerar ambos arquivos de memória, com respectivamente 64kB ou 32kB de espaço, é necessário usar um dos comandos:

	make (programa_alvo).pipeline.hex, ou make (programa_alvo).small.pipeline.hex

sendo "programa\_alvo" o programa a ser executado no processador. Feito isso e voltando ao diretório [HEX](HEX), é possivel encontrar dois
arquivos .hex que estão formatados da maneira que o leitor de arquivos do Verilog consegue entender. Por fim, para executar o programa é
necessário criar um link para o processador desejado e usar o script run\_verilator.sh (que possui algumas opções):
	
	
	ln -s (DIR)/(implementacao_alvo).v

	./run_verilator (implementacao_alvo).v (opção).

Para simular de maneira a apenas exibir a saída padrão use opção = "v" e para executar todos os Benchmarks use opção = "a". Caso o programa alvo seja algum Benchmark(CoreMark, Dhrystones ou Raystones) as informações de CPI e desempenho serão adicionadas a uma nova linha no arquivo do respectivo Benchmark no diretorio [INFO/BENCH](../INFO/BENCH).

