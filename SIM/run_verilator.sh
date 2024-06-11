(cd obj_dir; rm -f *.cpp *.o *.a VSOC)
verilator -CFLAGS '-I../../FIRMWARE/LIBFEMTORV32 -DSTANDALONE_FEMTOELF' -DBENCH -DBOARD_FREQ=10 -DCPU_FREQ=10 -DPASSTHROUGH_PLL -Wno-fatal \
	  --top-module SOC -cc -exe bench.cpp ../../FIRMWARE/LIBFEMTORV32/femto_elf.c $1


INFO_DIR="../INFO/BENCH"
NAME=$(cut -d. -f 1 firmware.txt)
echo $NAME

(cd obj_dir; make -f VSOC.mk)

if [ "$NAME" = "dhrystones" ]
then
	obj_dir/VSOC $2 #| grep -e CPI -e MIPS -e cycles -e instret | grep -Eo [0-9]+\.[0-9]+ | sed '1,2d' | sed '1i\'$1'' | column >> ${INFO_DIR}/dhrystones.txt

elif [ "$NAME" = "raystones" ]
then
	obj_dir/VSOC $2 | grep -e CPI -e RAYSTONES | grep -Eo [0-9]+\.[0-9]+ | sed '1d' | sed '1i\'$1'' | column -o"\t\t" >> ${INFO_DIR}/raystones.txt

elif [ "$NAME" = "coremark" ]
then
	obj_dir/VSOC $2 | grep -e CPI -e Coremark/MHz | grep -Eo [0-9]+\.[0-9]+ | sed '1i\'$1'' | column -o"\t\t" >> ${INFO_DIR}/coremark.txt

else
	obj_dir/VSOC $2
fi
