
changes:
	rm -rf src/core.sv
	ln -P ../../SIM/TORVS/$(v).sv src/core.sv
	echo "$(v)" > core.txt

change:
	rm -rf src/core.v
	ln -P ../../SIM/CORE/$(v).v src/core.v
	echo "$(v)" > core.txt

coremark:
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/COREMARK/PROGROM.hex ./src
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/COREMARK/DATARAM.hex ./src
	echo "coremark" > firmware.txt
	rm -rf ./src/GWDATARAM.hex
	cat ../../SIM/FIRMWARE/PRECOMPILED/RV32I/COREMARK/DATARAM.hex | tr [:blank:] [\\n] | awk 'NF' | tr 'a-z' 'A-Z' | sed '1s/^/#File_format=Hex\n#Address_depth=16384\n#Data_width=32\n/' > ./src/GWDATARAM.hex
	gw_sh gwsyn.tcl

dhrystones:
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/DHRYSTONES/PROGROM.hex ./src
	cp ../../SIM/FIRMWARE/PRECOMPILED/RV32I/DHRYSTONES/DATARAM.hex ./src
	rm -rf ./src/GWDATARAM.hex
	cat ../../SIM/FIRMWARE/PRECOMPILED/RV32I/DHRYSTONES/DATARAM.hex | tr [:blank:] [\\n] | awk 'NF' | tr 'a-z' 'A-Z' | sed '1s/^/#File_format=Hex\n#Address_depth=16384\n#Data_width=32\n/' > ./src/GWDATARAM.hex
	echo "dhrystones" > firmware.txt
	gw_sh gwsyn.tcl

raystones:
	cp ../../SIM/PRECOMPILED/RAYSTONES/PROGROM.hex ./src
	cp ../../SIM/PRECOMPILED/RAYSTONES/DATARAM.hex ./src
	echo "raystones" > firmware.txt
	rm -rf ./src/GWDATARAM.hex
	cat ../../SIM/PRECOMPILED/RAYSTONES/DATARAM.hex | tr [:blank:] [\\n] | awk 'NF' | tr 'a-z' 'A-Z' | sed '1s/^/#File_format=Hex\n#Address_depth=16384\n#Data_width=32\n/' > ./src/GWDATARAM.hex
	gw_sh gwsyn.tcl

all:
	cp ../../SIM/HEX/PROGROM.hex ./src
	cp ../../SIM/HEX/DATARAM.hex ./src
	gw_sh gwsyn.tcl

save:
	cp impl/pnr/PRIMER25k.fs ../DONE/primer25k/$(shell cat core.txt firmware.txt | tr -d "\n\r").fs

program:
	sudo openFPGALoader -b tangprimer25k /home/arruk/riscv/RTL/PRIMER25k/impl/pnr/PRIMER25k.fs
