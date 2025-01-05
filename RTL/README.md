# Síntese em FPGAs

O processo de síntese em FPGA acontece para a comprovação final da descrição de hardware feita. Este processo acontece de diferentes maneiras para diferentes placas de FPGAs, assim cada diretório subsequente identifica tais placas e seus respectivos processos. Em geral, o ambiente de síntese acontece em torno de um SOC que instancia um ambiente completo: processador, memória, UART, etc.

## Suporte

As placas atualmente suportadas são:

- Sipeed Tang Primer 25k: GW5A-LV25MG121NC1/I0 ([PRIMER25k](PRIMER25k))
	- Dependências: Gowin IDE (v1.10.9) e openFPGALoader.
- Intel DE10\_standard: Cyclone V 5CSXFC6D6F31C6 ([DE10S](DE10S))
	- Dependências: Quartus.

## Começando

Cada diretório tem um arquivo Makefile responsável pelo processo de síntese. Primeiramente, é preciso escolher qual o processador será utilizado através do comando:
	
	make change v=(processador alvo).

Agora, é preciso escolher qual Benchmark (dhrystones, raystones ou coremark) será utilizado para a síntese:

	make (benchmark) ou make all

para utilizar os binários presentes na pasta [HEX](../SIM/HEX). Assim, com o bitstream gerado, falta apenas queima-lo na placa:

	make program.

### Exemplo

A sequência

	make change v=core3 
	make coremark program

realiza a síntese do processador [core3](../SIM/CORE/core3.v) com a memória preenchida pelo benchmark Coremark, e carrega o bitstream gerado.

## Instrucoes para a UART

O resultado da execução é enviado via UART, então é necessário identificar a conexão da UART(caso não seja encontrado, use modprobe ftdi\_sio). Com a entrada do /dev/, é necessário configurar a porta com o mesmo baud rate utilizado na descrição de hardware

	sudo stty -F /dev/*** (BAUDRATE) cs8 -cstopb -parenb

Com isso pronto, só falta ler a porta, por exemplo através do comando
	
	cat /dev/***
