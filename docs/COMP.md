# EXECUÇÃO DE PROGRAMAS NO PROCESSADOR

## CRIAÇÃO DE ARQUIVOS EXECUTÁVEIS

O objetivo principal de qualquer processador é a execução de códigos, para qualquer objetivo que seja. Logo, existem dois aspectos fundamentais a serem observados: a criação e execução do código. Porém, existe entre estes dois aspectos a compilação, que tranformar o código, em linguagem de alto nível, em um arquivo executável, próprio para o processador utilizado.

Olhando para o nível mais baixo da execução de programas no processador apresentado, encontra-se a existencia de duas memórias, que são preenchidas no início da execução através de dois arquivos .hex. Estes dois arquivos são `DATARAM` (dados) e `PROGROM` (instruções), que possuem em cada linha 32bits de informação. Contudo, ainda existe a necessidade da criação destes arquivos apartir do processo de compilação citado anteriormente. Neste caso, será feita a compilação do código principal e algumas funções em C, e a montagem de códigos em assembly que auxiliarão a execução, tendo em vista que não existe sistema operacional e que a biblioteca padrão de IO não foi utilizada.

Um destes códigos de apoio é `start_pipeline.S` que será o arquivo crt, e tem como objetivo carregar o global pointer com o endereço base de IO e carregar o stack pointer com o valor 0x20000, o primeiro endereço após a memória de dados. Além desse, o arquivo `puchar.S` substitui a função nativa da libc para imprimir um caractere, para tal é usado o endereço base de IO, carregado no gp, com um offset igual a 8, já que o dispositivo encarregado de carregar a informação no terminal está configurado no bit 4 do endereço (1-hot-enconding). Com o endereço correto, basta carregar o conteúdo do registrador a0(x10), que é o primeiro argumento de qualquer chamada de função.

### BAREMETAL ELF
Arquivos executáveis são chamados de bare metal quando não existe sistema operacional, ou seja, cabe ao usuário algumas tarefas do SO. A primeira dependência se da pelo mapa de memória, gerado automaticamente pelo gcc, não estar de acordo com os padrões definidos, sendo eles, principalmente, o começo da memória de instruções e dados, e o arquivo crt. Portanto, são necessárias algumas configurações durante a compilação e vinculação, que são feitas através da regra `pipeline.hex` no arquivo [SIM/FIRMWARE/Makefile](SIM/FIRMWARE/Makefile) :

```
%.pipeline.elf: %.o start_pipeline.o $(LIBOBJECTS) $(RV_BINARIES)
        $(RVLD) -T pipeline.ld -m elf32lriscv -nostdlib -norelax $< $(LIBOBJECTS) -L$(RVTOOLCHAIN_LIB_DIR) -lm $(RVTOOLCHAIN_GCC_LIB_DIR)/libgcc.a  -o $@
        $(RVOBJDUMP) -Mnumeric -D $@ > $@.list
```
 - As flags definidas em `$(RVCFLAGS)` servem para que o gcc compile para o formato elf desejado, com `--no-relax` para que o global pointer não seja utilizado, já que é responsável por armazenar o endereço de IO.
 - A opção -T especifíca qual linker script será utilizado, no caso `pipeline.ld`, que define o mapa de memória próprio para este sistema.

Com o arquivo ELF executável, ainda falta adapta-lo em dois arquivos (contendo as informações em hexadecimal escritas em ASCII) para que possam ser lidos pelo Verilog. Para tal, é usado o programa [FIRMWARE/TOOLS/firmware_words](FIRMWARE/TOOLS/firmware_words), que através do arquivo .elf e de informações, sobre começo e fim da memória, consegue realizar a adaptação descrita.

