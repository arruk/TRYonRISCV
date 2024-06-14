(cd obj_dir; rm -f *.cpp *.o *.a VSOC)
verilator -CFLAGS '-I../../FIRMWARE/LIBFEMTORV32 -DSTANDALONE_FEMTOELF' -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal \
	  --top-module SOC -cc -exe bench.cpp ../../FIRMWARE/LIBFEMTORV32/femto_elf.c $1

PREC="PRECOMPILED"
INFO_DIR="../INFO/BENCH"
BENCH=$(cut -d. -f 1 firmware.txt)
echo $BENCH
IMPL=$(echo $1 | cut -d. -f 1 )
NO=$(echo "$1" | grep -Eo [0-9]+)


(cd obj_dir; make -f VSOC.mk)
if [ "$2" = "v" ]
then
	obj_dir/VSOC 

elif [ "$2" = "a" ]
then
	
	cp ${PREC}/RAYSTONES/DATARAM.hex ./ && cp ${PREC}/RAYSTONES/PROGROM.hex ./
	echo "raystones.pipeline.hex" > firmware.txt
	obj_dir/VSOC > ${INFO_DIR}/temp

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


	if [ $NO -gt 4 ]
	then
		cat ${INFO_DIR}/temp | grep -e CPI -e RAYSTONES -e Branch -e JAL -e JALR -e BHT -e BPH -e Cycles -e Instret \
				     | grep -Eo [0-9]+[.]?[0-9]* | sed '1,2d' | sed '1i\'$IMPL'' | rs -T >> ${INFO_DIR}/"$IMPL"/"$IMPL"_ray.txt

		cat ${INFO_DIR}/temp | grep -e CPI -e RAYSTONES | grep -Eo [0-9]+[.]?[0-9]* \
				     | sed '1,2d' | sed '1i\'$BIN'' | rs -T >> ${INFO_DIR}/raystones.txt

	else
		cat ${INFO_DIR}/temp | grep -e CPI -e RAYSTONES | grep -Eo [0-9]+[.]?[0-9]* \
				     | sed '1d' | sed '1i\'$IMPL'' | rs -T >> ${INFO_DIR}/raystones.txt
	fi

	cp ${PREC}/DHRYSTONES/DATARAM.hex ./ && cp ${PREC}/DHRYSTONES/PROGROM.hex ./
	echo "dhrystones.pipeline.hex" > firmware.txt
	obj_dir/VSOC > ${INFO_DIR}/temp

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
	
	if [ $NO -gt 4 ]
	then
		cat ${INFO_DIR}/temp | grep -e CPI -e MIPS -e cycles -e instret -e Branch -e JAL -e JALR -e BHT -e BPH \
				     | grep -E -o [0-9]+[.]?[0-9]*  | sed '1,2d' | sed '1i\'$IMPL'' | rs -T >> ${INFO_DIR}/"$IMPL"/"$IMPL"_dhry.txt

		cat ${INFO_DIR}/temp | grep -e CPI -e MIPS -e cycles -e instret | grep -Eo [0-9]+[.]?[0-9]* \
				     | sed '1,2d' | sed '1i\'$BIN'' | rs -T >> ${INFO_DIR}/dhrystones.txt

	else
		cat ${INFO_DIR}/temp | grep -e CPI -e MIPS -e cycles -e instret | grep -Eo [0-9]+[.]?[0-9]* \
				     | sed '1,2d' | sed '1i\'$IMPL'' | rs -T >> ${INFO_DIR}/dhrystones.txt
	fi


	cp ${PREC}/COREMARK/DATARAM.hex ./ && cp ${PREC}/COREMARK/PROGROM.hex ./
	echo "coremark.pipeline.hex" > firmware.txt
	obj_dir/VSOC > ${INFO_DIR}/temp

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

	if [ $NO -gt 4 ]
	then
		cat ${INFO_DIR}/temp | grep -e CPI -e Coremark/MHz -e Branch -e JAL -e JALR -e BHT -e BPH -e Cycles -e Instret \
				     | grep -Eo [0-9]+[.]?[0-9]* | sed '2d' | sed '1i\'$IMPL'' | rs -T >> ${INFO_DIR}/"$IMPL"/"$IMPL"_cmark.txt

		cat ${INFO_DIR}/temp | grep -e CPI -e Coremark/MHz | grep -Eo [0-9]+[.]?[0-9]* \
				     | sed '2d' | sed '1i\'$BIN'' | rs -T >> ${INFO_DIR}/coremark.txt
	else
		cat ${INFO_DIR}/temp | grep -e CPI -e Coremark/MHz | grep -Eo [0-9]+[.]?[0-9]* \
				     | sed '1i\'$IMPL'' | rs -T >> ${INFO_DIR}/coremark.txt
	fi


else
	# DIRECIONA A SAIDA PARA UM ARQUIVO TEMPORARIO
	obj_dir/VSOC > ${INFO_DIR}/temp

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

	# SELECAO DE QUAL BENCHMARK ESTA SENDO SIMULADO
	# A PARTIR DA IMPLEMENTACAO 5 EH NECESSARIO NAO SO DIFERENCIAR PELO NUMERO DA IMPLEMENTACAO, MAS COMO ELA ESTA CONFIGURADA (BIN)
	if [ "$BENCH" = "dhrystones" ]
	then
		if [ $NO -gt 4 ]
		then
			cat ${INFO_DIR}/temp | grep -e CPI -e MIPS -e cycles -e instret -e Branch -e JAL -e JALR -e BHT -e BPH \
					     | grep -E -o [0-9]+[.]?[0-9]*  | sed '1,2d' | sed '1i\'$IMPL'' | rs -T >> ${INFO_DIR}/"$IMPL"/"$IMPL"_dhry.txt
			
			cat ${INFO_DIR}/temp | grep -e CPI -e MIPS -e cycles -e instret | grep -Eo [0-9]+[.]?[0-9]* \
					     | sed '1,2d' | sed '1i\'$BIN'' | rs -T >> ${INFO_DIR}/dhrystones.txt	
			
		else	
			cat ${INFO_DIR}/temp | grep -e CPI -e MIPS -e cycles -e instret | grep -Eo [0-9]+[.]?[0-9]* \
					     | sed '1,2d' | sed '1i\'$IMPL'' | rs -T >> ${INFO_DIR}/dhrystones.txt	
		fi

	elif [ "$BENCH" = "raystones" ]
	then
		
		if [ $NO -gt 4 ]
		then
			cat ${INFO_DIR}/temp | grep -e CPI -e RAYSTONES -e Branch -e JAL -e JALR -e BHT -e BPH -e Cycles -e Instret \
					     | grep -Eo [0-9]+[.]?[0-9]* | sed '1,2d' | sed '1i\'$IMPL'' | rs -T >> ${INFO_DIR}/"$IMPL"/"$IMPL"_ray.txt

			cat ${INFO_DIR}/temp | grep -e CPI -e RAYSTONES | grep -Eo [0-9]+[.]?[0-9]* \
					     | sed '1,2d' | sed '1i\'$BIN'' | rs -T >> ${INFO_DIR}/raystones.txt

		else
			cat ${INFO_DIR}/temp | grep -e CPI -e RAYSTONES | grep -Eo [0-9]+[.]?[0-9]* \
					     | sed '1d' | sed '1i\'$IMPL'' | rs -T >> ${INFO_DIR}/raystones.txt
		fi

	elif [ "$BENCH" = "coremark" ]
	then
		if [ $NO -gt 4 ]
		then
			cat ${INFO_DIR}/temp | grep -e CPI -e Coremark/MHz -e Branch -e JAL -e JALR -e BHT -e BPH -e Cycles -e Instret \
					     | grep -Eo [0-9]+[.]?[0-9]* | sed '2d' | sed '1i\'$IMPL'' | rs -T >> ${INFO_DIR}/"$IMPL"/"$IMPL"_cmark.txt
			
			cat ${INFO_DIR}/temp | grep -e CPI -e Coremark/MHz | grep -Eo [0-9]+[.]?[0-9]* \
					     | sed '2d' | sed '1i\'$BIN'' | rs -T >> ${INFO_DIR}/coremark.txt
		else
			cat ${INFO_DIR}/temp | grep -e CPI -e Coremark/MHz | grep -Eo [0-9]+[.]?[0-9]* \
					     | sed '1i\'$IMPL'' | rs -T >> ${INFO_DIR}/coremark.txt
		fi

	else
		obj_dir/VSOC
	fi
fi
