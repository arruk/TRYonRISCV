change:
	rm -rf src/core.v
	ln -P ../../SIM/CORE/$(v).v src/core.v
	echo "$(v)" > core.txt

torvs:
	rm -rf src/core.sv
	ln -P ../../SIM/TORVS/$(v).sv src/core.sv
	echo "$(v)" > core.txt

coremark:
	cp ../../SIM/PRECOMPILED/COREMARK/PROGROM.hex ./src
	cp ../../SIM/PRECOMPILED/COREMARK/DATARAM.hex ./src
	cp mem/COREMARK.mif ./src/RAM.mif
	echo "coremark" > firmware.txt
	make -C impl/ all

dhrystones:
	cp ../../SIM/PRECOMPILED/DHRYSTONES/PROGROM.hex ./src
	cp mem/DHRYSTONES.mif ./src/RAM.mif
	echo "dhrystones" > firmware.txt
	make -C impl/ all

raystones:
	cp ../../SIM/PRECOMPILED/RAYSTONES/PROGROM.hex ./src
	cp ../../SIM/PRECOMPILED/RAYSTONES/DATARAM.hex ./src
	cp mem/RAYSTONES.mif ./src/RAM.mif
	echo "raystones" > firmware.txt
	make -C impl/ all

all:
	#cp ../../SIM/HEX/PROGROM.hex ./src
	#cp ../../SIM/HEX/DATARAM.hex ./src
	make -C impl/ all

clean:
	make -C impl/ clean

program:
	make -C impl/ program
