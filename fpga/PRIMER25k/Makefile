torvs:
	rm -rf src/core.sv
	ln -P ../../SIM/TORVS/$(v).sv src/core.sv
	echo "$(v)" > core.txt
	#echo "\`define TORVS\n\`define GOWIN" > src/config.v
change:
	rm -rf src/core.v
	ln -P ../../SIM/CORE/$(v).v src/core.v
	echo "$(v)" > core.txt

copy:
	cp ../../SIM/mem.sv ./src/
	cp ../../SIM/soc.v  ./src/
	cp ../../SIM/AUX/alu.v ./src/
	cp ../../SIM/AUX/clockworks.v ./src/
	cp ../../SIM/AUX/uart_tx.v ./src/

clean:
	rm -rf impl/gwsynthesis
	rm -rf impl/pnr
	rm -rf src/*.v
	rm -rf src/*.sv
	rm -rf src/*.hex

coremark:
	cp ../../SIM/PRECOMPILED/COREMARK/PROGROM.hex ./src
	cp ../../SIM/PRECOMPILED/COREMARK/DATARAM.hex ./src
	cat ../../SIM/PRECOMPILED/COREMARK/DATARAM.hex | tr [:blank:] [\\n] | awk 'NF' | tr 'a-z' 'A-Z' |  \
	    sed '1s/^/#File_format=Hex\n#Address_depth=16384\n#Data_width=32\n/' > ./src/GWDATARAM.hex
	echo "coremark" > firmware.txt
	gw_sh gwsyn.tcl

dhrystones:
	cp ../../SIM/PRECOMPILED/DHRYSTONES/PROGROM.hex ./src
	cp ../../SIM/PRECOMPILED/DHRYSTONES/DATARAM.hex ./src
	cat ../../SIM/PRECOMPILED/DHRYSTONES/DATARAM.hex | tr [:blank:] [\\n]  | grep -v ^$ | tr 'a-z' 'A-Z' |sed '1s/^/#File_format=Hex\n#Address_depth=16384\n#Data_width=32\n/' > ./src/GWDATARAM.hex
	echo "dhrystones" > firmware.txt
	#gw_sh gwsyn.tcl

raystones:
	cp ../../SIM/PRECOMPILED/RAYSTONES/PROGROM.hex ./src
	cp ../../SIM/PRECOMPILED/RAYSTONES/DATARAM.hex ./src
	cat ../../SIM/PRECOMPILED/RAYSTONES/DATARAM.hex | tr [:blank:] [\\n] | awk 'NF' | tr 'a-z' 'A-Z' | \
	    sed '1s/^/#File_format=Hex\n#Address_depth=16384\n#Data_width=32\n/' > ./src/GWDATARAM.hex
	echo "raystones" > firmware.txt
	gw_sh gwsyn.tcl

all:
	gw_sh gwsyn.tcl

save:
	cp impl/pnr/PRIMER25k.fs ../DONE/primer25k/$(shell cat core.txt firmware.txt | tr -d "\n\r").fs

program:
	openFPGALoader -b tangprimer25k impl/pnr/PRIMER25k.fs
