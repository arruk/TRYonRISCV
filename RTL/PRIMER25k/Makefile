change:
	rm -rf src/core.v
	ln -P ../../SIM/CORE/$(v).v src/core.v
	echo "$(v)" > core.txt

coremark:
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/COREMARK/PROGROM.hex ./src
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/COREMARK/DATARAM.hex ./src
	gw_sh gwsyn.tcl

dhrystones:
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/DHRYSTONES/PROGROM.hex ./src
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/DHRYSTONES/DATARAM.hex ./src
	gw_sh gwsyn.tcl

raystones:
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/RAYSTONES/PROGROM.hex ./src
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/RAYSTONES/DATARAM.hex ./src
	gw_sh gwsyn.tcl

all:
	cp ../../SIM/HEX/PROGROM.hex ./src
	cp ../../SIM/HEX/DATARAM.hex ./src
	gw_sh gwsyn.tcl

program:
	sudo openFPGALoader -b tangprimer25k /home/arruk/TRYonRISCV/RTL/PRIMER25k/impl/pnr/PRIMER25k.fs
