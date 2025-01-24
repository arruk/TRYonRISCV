HEXDIR="../../SIM/PRECOMPILED"
TORVS="../../SIM/TORVS"

main(){

	if [ $1 = "r" ]
	then

		rm -rf impl/pnr/
		rm -rf impl/impl/gwsynthesis/
                gw_sh gwsyn.tcl

	elif [ $1 = "p" ]
	then
		
		openFPGALoader -b tangprimer25k impl/pnr/PRIMER25k.fs

	elif [ $1 = "c" ]
	then
	
                cp $TORVS/$2.sv src/
                echo $2 > core.txt

                cp ../../SIM/mem.sv ./src/
                cp ../../SIM/soc.v  ./src/
                cp ../../SIM/AUX/alu.v ./src/
                cp ../../SIM/AUX/clockworks.v ./src/
                cp ../../SIM/AUX/uart_tx.v ./src/
		
	elif [ $1 = "dhrystones" ]
	then
		#cp $TORVS/$2.sv src/
		#echo $2 > core.txt

		#cp ../../SIM/mem.sv ./src/
		#cp ../../SIM/soc.v  ./src/
		#cp ../../SIM/AUX/alu.v ./src/
		#cp ../../SIM/AUX/clockworks.v ./src/
		#cp ../../SIM/AUX/uart_tx.v ./src/

        	cp $HEXDIR/DHRYSTONES/PROGROM.hex src/
        	cp $HEXDIR/DHRYSTONES/DATARAM.hex src/
	        cat $HEXDIR/DHRYSTONES/DATARAM.hex | tr [:blank:] [\\n]  | grep -v ^$ | tr 'a-z' 'A-Z' | \
		    sed '1s/^/#File_format=Hex\n#Address_depth=16384\n#Data_width=32\n/' > ./src/GWDATARAM.hex

 		echo "dhrystones" > firmware.txt

		#gw_sh gwsyn.tcl

	elif [ $1 = "raystones" ]
	then

        	cp $HEXDIR/DHRYSTONES/PROGROM.hex src/
        	cp $HEXDIR/DHRYSTONES/DATARAM.hex src/
	        cat $HEXDIR/DHRYSTONES/DATARAM.hex | tr [:blank:] [\\n]  | grep -v ^$ | tr 'a-z' 'A-Z' | \
		    sed '1s/^/#File_format=Hex\n#Address_depth=16384\n#Data_width=32\n/' > ./src/GWDATARAM.hex

 		echo "dhrystones" > firmware.txt


	elif [ $1 = "coremark" ]
	then

        	cp $HEXDIR/DHRYSTONES/PROGROM.hex src/
        	cp $HEXDIR/DHRYSTONES/DATARAM.hex src/
	        cat $HEXDIR/DHRYSTONES/DATARAM.hex | tr [:blank:] [\\n]  | grep -v ^$ | tr 'a-z' 'A-Z' | \
		    sed '1s/^/#File_format=Hex\n#Address_depth=16384\n#Data_width=32\n/' > ./src/GWDATARAM.hex

 		echo "dhrystones" > firmware.txt

	else

		echo "WRONG ARGUMENTS"

	fi

}

echo "STARTING SCRIPT"
main "$@"
exit
