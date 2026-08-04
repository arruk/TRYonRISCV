INFO="../../INFO/BOARDS/PRIMER25k/"

main () {

	make all

	BENCH=$(cat firmware.txt)
	CPU=$(cat core.txt)

	FIT=$(cat impl/pnr/PRIMER25k.rpt.txt | grep -e "Logic  " -e "Register  " -e "CLS  " -e BSRAM | cut -f2 -d"|" | cut -f1 -d"/" | tr -d " "| sed '1i\'$CPU'' | paste -sd",")
	STA=$(cat impl/gwsynthesis/PRIMER25k_syn.rpt.html impl/pnr/PRIMER25k_tr_content.html | grep -e MHz | sed '1,2d' | sed '2,3d' | cut -f1 -d"(" | cut -f2 -d">" | paste -sd",")	

	if [ $BENCH = "dhrystones" ]
	then

		echo "DHRYSTONES"
		echo $FIT,$STA >> ${INFO}/dhrystones_wfifo.csv

	elif [ $BENCH = "raystones" ]
	then

		echo "RAYSTONES"
		echo $FIT,$STA >> ${INFO}/raystones.csv

	elif [ $BENCH = "coremark" ]
	then

		echo "COREMARK"
		echo $FIT,$STA >> ${INFO}/coremark.csv

	fi

	make program
	#cp impl/pnr/PRIMER25k.fs ../DONE/primer25k/"$CPU$BENCH".fs

}

echo "STARTING SCRIPT"

for i in {1..1}
do
        rm -rf src/core.sv
	#ln -P ../../SIM/TORVS/torvs8p$i.sv src/core.sv
	cp ../../SIM/TORVS/"torvs9p$i".sv src/core.sv
        echo "torvs9p$i" > core.txt

	#cp ../../SIM/PRECOMPILED/DHRYSTONES/PROGROM.hex src/
	#cp -r mem/dhrystones/gowin_dpb/ ./src
        echo "dhrystones" > firmware.txt	
	main "@"	
	#cp ../../SIM/PRECOMPILED/RAYSTONES/PROGROM.hex src/
	#cp -r mem/raystones/gowin_dpb/ ./src
        #echo "raystones" > firmware.txt
	#main "@"	
	#cp ../../SIM/PRECOMPILED/COREMARK/PROGROM.hex src/
	#cp -r mem/raystones/gowin_dpb/ ./src
        #echo "coremark" > firmware.txt
	#main "@"	


done

exit

