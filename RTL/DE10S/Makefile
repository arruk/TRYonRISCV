change:
	rm -rf src/core.v
	ln -P ../../SIM/CORE/$(v).v src/core.v
	echo "$(v)" > core.txt

coremark:
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/COREMARK/PROGROM.hex ./src
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/COREMARK/DATARAM.hex ./src
	echo "coremark" > firmware.txt
	make -C impl/ all

dhrystones:
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/DHRYSTONES/PROGROM.hex ./src
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/DHRYSTONES/DATARAM.hex ./src
	echo "coremark" > firmware.txt
	make -C impl/ all

raystones:
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/RAYSTONES/PROGROM.hex ./src
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/RAYSTONES/DATARAM.hex ./src
	echo "coremark" > firmware.txt
	make -C impl/ all

all:
	cp ../../SIM/HEX/PROGROM.hex ./src
	cp ../../SIM/HEX/DATARAM.hex ./src
	make -C impl/ all

clean:
	make -C impl/ clean

program:
	make -C impl/ program
