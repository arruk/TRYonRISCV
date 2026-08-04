#!/usr/bin/env bash
set -euo pipefail

SIM_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SIM_DIR/.." && pwd)"

RTL_DIR="$REPO_ROOT/rtl"
SOC_DIR="$RTL_DIR/soc"
COMMON_DIR="$RTL_DIR/common"
TORV_DIR="$RTL_DIR/cores/torv"
TORVS_DIR="$RTL_DIR/cores/torvs"

CORE_NAME="$1"

if [[ -f "$TORVS_DIR/$CORE_NAME" ]]; then
	CORE_FILE="$TORVS_DIR/$CORE_NAME"
	CPU_TYPE="TORVS"
elif [[ -f "$TORV_DIR/$CORE_NAME" ]]; then
	CORE_FILE="$TORV_DIR/$CORE_NAME"
	CPU_TYPE="TORV"
else
	echo "Core não encontrado: $CORE_NAME" >&2
	exit 1
fi

IMPL="${CORE_NAME%.*}"
OBJ_DIR="$REPO_ROOT/build/sim/$IMPL/obj_dir"

SOURCES=(
	"$SOC_DIR/soc.v"
	"$SOC_DIR/mem.sv"
	"$COMMON_DIR/clockworks.v"
	"$COMMON_DIR/uart_tx.v"
	"$CORE_FILE"
)

if [[ "$CPU_TYPE" == "TORV" ]]; then
	if [[ "$IMPL" == "torv6" ]]; then
		SOURCES+=("$COMMON_DIR/alu_old.v")
	else
		SOURCES+=("$COMMON_DIR/alu.v")
	fi
fi

main() {

	#(cd obj_dir; rm -f *.cpp *.o *.a VSOC)

	PREC="PRECOMPILED"
	#BENCH=$(cut -d. -f 1 firmware.txt)

	if [ "$2" = "v" ]
	then
		#echo $BENCH
		
		mkdir -p "$OBJ_DIR"
		verilator "-D$CPU_TYPE" -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal --Mdir "$OBJ_DIR" --top-module SOC --cc --exe "$SIM_DIR/bench.cpp" "${SOURCES[@]}"		
		make -C "$OBJ_DIR" -f VSOC.mk
		cd "$SIM_DIR"
		"$OBJ_DIR/VSOC"

		#verilator -D$CORE -D$CPUT -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal --top-module SOC -cc -exe bench.cpp soc.v
		#(cd obj_dir; make -f VSOC.mk)
		#obj_dir/VSOC 

	elif [ "$2" = "a" ]
	then	
		
		verilator  -D$CORE -D$CPUT -D$DEFINE -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal \
			  --top-module SOC -cc -exe bench.cpp soc.v
		
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
		
		verilator -D$CORE -D$CPUT -D$DEFINE -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal \
			  --top-module SOC -cc -exe bench.cpp soc.v
		
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
