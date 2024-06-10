#BOARD=tangnano9k
#FAMILY=GW1N-9C
#DEVICE=GW1NR-LV9QN88PC6/I5
BOARD=primer20k
FAMILY=GW2A-18
DEVICE=GW2A-LV18PG256C8/I7

# rm -rf obj_dir 
mkdir obj_dir

if [ -d "obj_dir" ]; then
    rm -r obj_dir/core.json obj_dir/core_pnr.json obj_dir/core.fs
fi

yosys -p "read_verilog pipeline7.v ; synth_gowin -noalu -nowidelut -top SOC -json obj_dir/core.json"


if [ -f "obj_dir/core.json" ]; then
    nextpnr-himbaechel -l info.txt --json obj_dir/core.json --write obj_dir/core_pnr.json --device ${DEVICE} --vopt family=${FAMILY} --vopt cst=${BOARD}.cst
fi


#if [ -f "obj_dir/core_pnr.json" ]; then
#    gowin_pack -d ${FAMILY} -o obj_dir/core.fs obj_dir/core_pnr.json
#fi



