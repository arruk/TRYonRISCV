PREC="PRECOMPILED"
INFO_DIR="../INFO/BENCH/TORVS"
BENCH=$(cut -d. -f 1 firmware.txt)
NO=$(echo "$1" | grep -Eo [0-9]+)
SZ=4
N=0
M=0


main() {

	(cd obj_dir; rm -f *.cpp *.o *.a VSOC)

	if [ "$2" = "v" ]
	then
		echo $BENCH
		
		verilator -CFLAGS '-I../../FIRMWARE/LIBFEMTORV32 -DSTANDALONE_FEMTOELF' -D$CORE -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal \
   			  --top-module SOC -cc -exe bench.cpp ../../FIRMWARE/LIBFEMTORV32/femto_elf.c soc.v
	
		(cd obj_dir; make -f VSOC.mk)
		
		obj_dir/VSOC 

	elif [ "$2" = "a" ]
	then	
		
		verilator -CFLAGS '-I../../FIRMWARE/LIBFEMTORV32 -DSTANDALONE_FEMTOELF' -D$CORE -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal \
			  --top-module SOC -cc -exe bench.cpp ../../FIRMWARE/LIBFEMTORV32/femto_elf.c soc.v
		
		(cd obj_dir; make -f VSOC.mk)
		
		cp ${PREC}/RAYSTONES/DATARAM.hex HEX/ && cp ${PREC}/RAYSTONES/PROGROM.hex HEX/
		echo "raystones.pipeline.hex" > firmware.txt
		BENCH=$(cut -d. -f 1 firmware.txt)
		echo $BENCH
		obj_dir/VSOC > ${INFO_DIR}/temp
		rayst_parse	

		#cp ${PREC}/DHRYSTONES/DATARAM.hex HEX/ && cp ${PREC}/DHRYSTONES/PROGROM.hex HEX/
		#echo "dhrystones.pipeline.hex" > firmware.txt
		#BENCH=$(cut -d. -f 1 firmware.txt)
		#echo $BENCH
		#obj_dir/VSOC > ${INFO_DIR}/temp
		#dhry_parse

		cp ${PREC}/COREMARK/DATARAM.hex HEX/ && cp ${PREC}/COREMARK/PROGROM.hex HEX/
		echo "coremark.pipeline.hex" > firmware.txt
		BENCH=$(cut -d. -f 1 firmware.txt)
		echo $BENCH
		obj_dir/VSOC > ${INFO_DIR}/temp
		cmark_parse

	else

		echo "WRONG ARGUMENTS"

	fi
}

branch_info(){
        # ARMAZENA EM BIN(BRANCH INFORMATION) OS VALORES DO TAMANHO DA BRANCH HISTORY TABLE E DO VETOR DO BRANCH HISTORY
        BHT=$(grep -e BHT ${INFO_DIR}/temp | grep -Eo [0-9]+[.]?[0-9]* )
        BH=$( grep -e BPH ${INFO_DIR}/temp | grep -Eo [0-9]+[.]?[0-9]* )
        BIN="("
        if [ -n "$BHT" ]
        then
                BIN="$BIN$BHT"
        fi
        if [ -n "$BH" ]
        then
                BIN="$BIN,$BH"
        fi
        BIN="$IMPL$BIN)"
}

rayst_parse(){
	#if [ $NO -gt 2 ]
	#then
	#	cat ${INFO_DIR}/temp | grep -e CPI -e RAYSTONES -e Branch -e JAL -e JALR -e BHT -e BPH -e Cycles -e Instret \
	#			     | grep -Eo [0-9]+[.]?[0-9]* | sed '1,2d' | sed '1i\'$IMPL'' | paste -sd, >> ${INFO_DIR}/"$IMPL"/raystones.csv
	#	IMPL_T=$BIN
	#fi
	cat ${INFO_DIR}/temp | grep -e CPI -e RAYSTONES -e Cycles -e Instret | grep -Eo [0-9]+[.]?[0-9]* \
			     | sed '1,2d' | sed '3,4d' | sed '3,4d' | sed '3,4d' | sed '1i\'$IMPL_T'' | paste -sd, >> ${INFO_DIR}/raystones.csv
	IMPL_T=$IMPL
}

dhry_parse(){
	#if [ $NO -gt 2 ]
	#then
	#	cat ${INFO_DIR}/temp | grep -e CPI -e MIPS -e cycles -e instret -e Branch -e JAL -e JALR -e BHT -e BPH \
	#			     | grep -E -o [0-9]+[.]?[0-9]*  | sed '1,2d' | sed '1i\'$IMPL'' | paste -sd, >> ${INFO_DIR}/"$IMPL"/dhrystones.csv
	#	IMPL_T=$BIN
	#fi
	cat ${INFO_DIR}/temp | grep -e CPI -e MIPS -e cycles -e instret | grep -Eo [0-9]+[.]?[0-9]* \
			     | sed '1,2d' | sed '1i\'$IMPL_T'' | paste -sd, >> ${INFO_DIR}/dhrystones.csv
	IMPL_T=$IMPL
}

cmark_parse(){
	#if [ $NO -gt 2 ]
	#then
	#	cat ${INFO_DIR}/temp | grep -e CPI -e Coremark/MHz -e Branch -e JAL -e JALR -e BHT -e BPH -e Cycles -e Instret \
	#			     | grep -Eo [0-9]+[.]?[0-9]* | sed '2d' | sed '1i\'$IMPL'' | paste -sd, >> ${INFO_DIR}/"$IMPL"/coremark.csv
	#	IMPL_T=$BIN
	#fi
	cat ${INFO_DIR}/temp | grep -e CPI -e Coremark/MHz -e Cycles -e Instret | grep -Eo [0-9]+[.]?[0-9]* \
			     | sed '2d' | sed '1i\'$IMPL_T'' | paste -sd, >> ${INFO_DIR}/coremark.csv
	IMPL_T=$IMPL	
}

if [ "$2" = "a" ]
then
	for i in {5..5}
	do
		CORE="TORVS6P$i" #$(echo $1 | cut -d. -f 1 | tr 'a-z' 'A-Z' )
		IMPL="torvs6p$i"
	        IMPL_T=$IMPL	
		echo "STARTING $CORE"
		main "$@"
		echo "FINISHED IN $CORE"
	done
else
	CORE=$(echo $1 | cut -d. -f 1 | tr 'a-z' 'A-Z' )
	IMPL=$(echo $1 | cut -d. -f 1)
	IMPL_T=$IMPL
	main "$@"
fi

exit
