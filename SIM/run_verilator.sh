main() {

	(cd obj_dir; rm -f *.cpp *.o *.a VSOC)

	PREC="PRECOMPILED"
	BENCH=$(cut -d. -f 1 firmware.txt)

	if [ "$2" = "v" ]
	then
		echo $BENCH
		
		verilator -CFLAGS '-I../../FIRMWARE/LIBFEMTORV32 -DSTANDALONE_FEMTOELF' -D$CORE -D$CPUT -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal \
   			  --top-module SOC -cc -exe bench.cpp ../../FIRMWARE/LIBFEMTORV32/femto_elf.c soc.v
	
		(cd obj_dir; make -f VSOC.mk)
		
		obj_dir/VSOC 

	elif [ "$2" = "a" ]
	then	
		
		verilator -CFLAGS '-I../../FIRMWARE/LIBFEMTORV32 -DSTANDALONE_FEMTOELF' -D$CORE -D$CPUT -D$DEFINE -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal \
			  --top-module SOC -cc -exe bench.cpp ../../FIRMWARE/LIBFEMTORV32/femto_elf.c soc.v
		
		(cd obj_dir; make -f VSOC.mk)
		
		cp ${PREC}/RAYSTONES/DATARAM.hex HEX/ && cp ${PREC}/RAYSTONES/PROGROM.hex HEX/
		echo "raystones.pipeline.hex" > firmware.txt
		BENCH=$(cut -d. -f 1 firmware.txt)
		echo $BENCH
		obj_dir/VSOC > ${INFO_DIR}/temp
		rayst_parse	

		cp ${PREC}/DHRYSTONES/DATARAM.hex HEX/ && cp ${PREC}/DHRYSTONES/PROGROM.hex HEX/
		echo "dhrystones.pipeline.hex" > firmware.txt
		BENCH=$(cut -d. -f 1 firmware.txt)
		echo $BENCH
		obj_dir/VSOC > ${INFO_DIR}/temp
		dhry_parse

		cp ${PREC}/COREMARK/DATARAM.hex HEX/ && cp ${PREC}/COREMARK/PROGROM.hex HEX/
		echo "coremark.pipeline.hex" > firmware.txt
		BENCH=$(cut -d. -f 1 firmware.txt)
		echo $BENCH
		obj_dir/VSOC > ${INFO_DIR}/temp
		cmark_parse

	elif [ "$2" = "b" ]
	then	
		
		verilator -CFLAGS '-I../../FIRMWARE/LIBFEMTORV32 -DSTANDALONE_FEMTOELF' -D$CORE -D$CPUT -D$DEFINE -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal \
			  --top-module SOC -cc -exe bench.cpp ../../FIRMWARE/LIBFEMTORV32/femto_elf.c soc.v
		
		(cd obj_dir; make -f VSOC.mk)
		
		cp ${PREC}/RAYSTONES/DATARAM.hex HEX/ && cp ${PREC}/RAYSTONES/PROGROM.hex HEX/
		echo "raystones.pipeline.hex" > firmware.txt
		BENCH=$(cut -d. -f 1 firmware.txt)
		echo $BENCH
		obj_dir/VSOC

		cp ${PREC}/DHRYSTONES/DATARAM.hex HEX/ && cp ${PREC}/DHRYSTONES/PROGROM.hex HEX/
		echo "dhrystones.pipeline.hex" > firmware.txt
		BENCH=$(cut -d. -f 1 firmware.txt)
		echo $BENCH
		obj_dir/VSOC

		cp ${PREC}/COREMARK/DATARAM.hex HEX/ && cp ${PREC}/COREMARK/PROGROM.hex HEX/
		echo "coremark.pipeline.hex" > firmware.txt
		BENCH=$(cut -d. -f 1 firmware.txt)
		echo $BENCH
		obj_dir/VSOC

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
	#cat ${INFO_DIR}/temp | grep -e CPI -e RAYSTONES -e Cycles -e Instret | grep -Eo [0-9]+[.]?[0-9]* \
	#		     | sed '1,2d' | sed '3,4d' | sed '3,4d' | sed '3,4d' | sed '1i\'$IMPL_T'' | paste -sd, >> ${INFO_DIR}/raystones.csv
	cat ${INFO_DIR}/temp | grep -e CPI -e RAYSTONES -e Cycles -e Instret | grep -Eo [0-9]+[.]?[0-9]* \
			     | sed '1,2d' | sed '1i\'$IMPL_T'' | paste -sd, >> ${INFO_DIR}/raystones.csv
	IMPL_T=$IMPL
}

dhry_parse(){
	#if [ $NO -gt 2 ]
	#then
	#	cat ${INFO_DIR}/temp | grep -e CPI -e MIPS -e cycles -e instret -e Branch -e JAL -e JALR -e BHT -e BPH \
	#			     | grep -E -o [0-9]+[.]?[0-9]*  | sed '1,2d' | sed '1i\'$IMPL'' | paste -sd, >> ${INFO_DIR}/"$IMPL"/dhrystones.csv
	#	IMPL_T=$BIN
	#f2
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
	#declare -a arr=("x" "STORE_IN_B" "LOAD_IN_B" "BTYPE_IN_B")
	declare -a arr=("LOAD_IN_B" "BTYPE_IN_B")
	for i in 9
	do
		for j in "${arr[@]}"
		do
			CORE="TORVS"$i"C" 
			IMPL="torvs"$i"C"
			IMPL_T=$IMPL	
			CPUT="TORVS"
			#ln -s TORVS/$IMPL.sv
			INFO_DIR="../INFO/BENCH/TORVS"
			DEFINE=$j
			#echo "$DEFINE"

			echo "STARTING $CORE"
			main "$@"
			#rm -rf $IMPL.sv
			echo "FINISHED IN $CORE"
		done
	done
else
	CORE=$(echo $1 | cut -d. -f 1 | tr 'a-z' 'A-Z' )
	IMPL=$(echo $1 | cut -d. -f 1)
	IMPL_T=$IMPL
	CPUT="TORV"#$(echo $1 | sed 's/[0-9].*//' | tr 'a-z' 'A-Z')
	main "$@"
fi

exit
