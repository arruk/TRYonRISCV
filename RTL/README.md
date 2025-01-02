# Instrucoes para a UART

- Identificar as portas
	sudo modprobe ftdi_sio
- Localizar a UART
	sudo udevadm info /dev/ttyUSB
- Configurar a porta
	sudo stty -F /dev/ttyUSB 9600 cs8 -cstopb -parenb
- Ler da UART
	sudo cat /dev/ttyUSB
