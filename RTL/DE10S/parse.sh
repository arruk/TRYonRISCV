INFO="../../INFO/BOARDS/DE10S"

main () {

	make clean all

	BENCH=$(cat firmware.txt)
	CPU=$(cat core.txt)

	FIT=$(cat impl/proj.fit.summary | grep -e ALM -e registers -e block -e RAM | cut -f1 -d"/" | cut -f2 -d":" | tr -d , | tr -d " " | sed '1i\'$CPU'' | paste -sd",")
	STA=$(cat impl/proj.sta.rpt | grep -e "Restricted Fmax" -A 2 | sed '1,2d' | sed '2,3d' | sed '2d' | cut -c2- | cut -f1 -d"M" | tr -d " " | paste -sd",")	

	if [ $BENCH = "dhrystones" ]
	then

		echo "DHRYSTONES"
		echo $FIT,$STA >> ${INFO}/dhrystones.csv

	elif [ $BENCH = "raystones" ]
	then

		echo "RAYSTONES"
		echo $FIT,$STA >> ${INFO}/raystones.csv

	elif [ $BENCH = "coremark" ]
	then

		echo "COREMARK"
		echo $FIT,$STA >> ${INFO}/coremark.csv

	fi

	#make program

}

echo "STARTING SCRIPT"

for i in {1..5}
do
        rm -rf src/core.sv
	#ln -P ../../SIM/TORVS/torvs8p$i.sv src/core.sv
	cp ../../SIM/TORVS/torvs5p$i.sv src/core.sv
        echo "torvs5p$i" > core.txt

	#cp ../../SIM/PRECOMPILED/DHRYSTONES/PROGROM.hex src/
	#cp mem/DHRYSTONES.mif ./src/RAM.mif
        #echo "dhrystones" > firmware.txt
	main "@"	
	#cp ../../SIM/PRECOMPILED/RAYSTONES/PROGROM.hex src/
	#cp mem/RAYSTONES.mif ./src/RAM.mif
        #echo "raystones" > firmware.txt
	#main "@"	
	#cp ../../SIM/PRECOMPILED/COREMARK/PROGROM.hex src/
	#cp mem/COREMARK.mif ./src/RAM.mif
        #echo "coremark" > firmware.txt
	#main "@"	


done

exit
