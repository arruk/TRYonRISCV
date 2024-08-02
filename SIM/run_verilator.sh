PREC="PRECOMPILED"
INFO_DIR="../INFO/BENCH"
BENCH=$(cut -d. -f 1 firmware.txt)
echo $BENCH
IMPL=$(echo $1 | cut -d. -f 1)
IMPL_T=$IMPL
CORE=$(echo $1 | cut -d. -f 1 | tr 'a-z' 'A-Z' )
NO=$(echo "$1" | grep -Eo [0-9]+)
SZ=4



main() {

	(cd obj_dir; rm -f *.cpp *.o *.a VSOC)
	verilator -CFLAGS '-I../../FIRMWARE/LIBFEMTORV32 -DSTANDALONE_FEMTOELF' -D$CORE -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal \
		  --top-module SOC -cc -exe bench.cpp ../../FIRMWARE/LIBFEMTORV32/femto_elf.c soc.v
	#verilator -CFLAGS '-I../../FIRMWARE/LIBFEMTORV32 -DSTANDALONE_FEMTOELF' -Gsz=$SZ -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal \
	#	  --top-module SOC -cc -exe bench.cpp ../../FIRMWARE/LIBFEMTORV32/femto_elf.c $1
	
	(cd obj_dir; make -f VSOC.mk)
	if [ "$2" = "v" ]
	then
		obj_dir/VSOC 
	elif [ "$2" = "a" ]
	then	
		
		cp ${PREC}/RAYSTONES/DATARAM.hex ./ && cp ${PREC}/RAYSTONES/PROGROM.hex ./
		echo "raystones.pipeline.hex" > firmware.txt
		obj_dir/VSOC #> ${INFO_DIR}/temp

		#branch_info
		#rayst_parse	

		cp ${PREC}/DHRYSTONES/DATARAM.hex ./ && cp ${PREC}/DHRYSTONES/PROGROM.hex ./
		echo "dhrystones.pipeline.hex" > firmware.txt
		obj_dir/VSOC #> ${INFO_DIR}/temp

		#branch_info
		#dhry_parse

		cp ${PREC}/COREMARK/DATARAM.hex ./ && cp ${PREC}/COREMARK/PROGROM.hex ./
		echo "coremark.pipeline.hex" > firmware.txt
		obj_dir/VSOC #> ${INFO_DIR}/temp

		#branch_info
		#cmark_parse

	else
		# DIRECIONA A SAIDA PARA UM ARQUIVO TEMPORARIO
		obj_dir/VSOC > ${INFO_DIR}/temp

		branch_info
		echo $BIN

		# SELECAO DE QUAL BENCHMARK ESTA SENDO SIMULADO
		# A PARTIR DA IMPLEMENTACAO 5 EH NECESSARIO NAO SO DIFERENCIAR PELO NUMERO DA IMPLEMENTACAO, MAS COMO ELA ESTA CONFIGURADA (BIN)
		if [ "$BENCH" = "dhrystones" ]
		then
			dhry_parse
		elif [ "$BENCH" = "raystones" ]
		then
			rayst_parse
		elif [ "$BENCH" = "coremark" ]
		then
			cmark_parse
		else
			obj_dir/VSOC
		fi
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
	if [ $NO -gt 4 ]
	then
		cat ${INFO_DIR}/temp | grep -e CPI -e RAYSTONES -e Branch -e JAL -e JALR -e BHT -e BPH -e Cycles -e Instret \
				     | grep -Eo [0-9]+[.]?[0-9]* | sed '1,2d' | sed '1i\'$IMPL'' | paste -sd, >> ${INFO_DIR}/"$IMPL"/raystones.csv
		IMPL_T=$BIN
	fi
	cat ${INFO_DIR}/temp | grep -e CPI -e RAYSTONES | grep -Eo [0-9]+[.]?[0-9]* \
			     | sed '1,2d' | sed '1i\'$IMPL_T'' | paste -sd, >> ${INFO_DIR}/raystones.csv
	IMPL_T=$IMPL
}

dhry_parse(){
	if [ $NO -gt 4 ]
	then
		cat ${INFO_DIR}/temp | grep -e CPI -e MIPS -e cycles -e instret -e Branch -e JAL -e JALR -e BHT -e BPH \
				     | grep -E -o [0-9]+[.]?[0-9]*  | sed '1,2d' | sed '1i\'$IMPL'' | paste -sd, >> ${INFO_DIR}/"$IMPL"/dhrystones.csv
		IMPL_T=$BIN

	fi
	cat ${INFO_DIR}/temp | grep -e CPI -e MIPS -e cycles -e instret | grep -Eo [0-9]+[.]?[0-9]* \
			     | sed '1,2d' | sed '1i\'$IMPL_T'' | paste -sd, >> ${INFO_DIR}/dhrystones.csv
	IMPL_T=$IMPL
}

cmark_parse(){
	if [ $NO -gt 4 ]
	then
		cat ${INFO_DIR}/temp | grep -e CPI -e Coremark/MHz -e Branch -e JAL -e JALR -e BHT -e BPH -e Cycles -e Instret \
				     | grep -Eo [0-9]+[.]?[0-9]* | sed '2d' | sed '1i\'$IMPL'' | paste -sd, >> ${INFO_DIR}/"$IMPL"/coremark.csv
		IMPL_T=$BIN
	fi
	cat ${INFO_DIR}/temp | grep -e CPI -e Coremark/MHz | grep -Eo [0-9]+[.]?[0-9]* \
			     | sed '2d' | sed '1i\'$IMPL_T'' | paste -sd, >> ${INFO_DIR}/coremark.csv
	IMPL_T=$IMPL	
}

if [ "$2" = "a" ]
then
	for i in {5..16}
	do
		SZ=$i
		main "$@"
		echo "FINISHED WITH $SZ bits\n"
	done
else
	SZ=14
	main "$@"
fi

exit
