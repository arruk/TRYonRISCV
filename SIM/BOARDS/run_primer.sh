BOARD=primer20k
FAMILY=GW2A-18
DEVICE=GW2A-LV18PG256C8/I7
BOARD_FREQ=100
CPU_FREQ=100

PROJ="SOC"
INFO_DIR="../INFO/BOARDS"
NAME=$(echo $1 | cut -d. -f 1 )

yosys -DPRIMER -DALU -q -p "synth_gowin -noalu -nowidelut -top $PROJ -json BOARDS/$NAME.json" $1
nextpnr-himbaechel -l ${INFO_DIR}/${NAME}.txt --json BOARDS/${NAME}.json --write BOARDS/${NAME}pnr.json --device ${DEVICE} --vopt family=${FAMILY} --vopt cst=BOARDS/${BOARD}.cst
gowin_pack -d ${FAMILY} -o BOARDS/${NAME}.fs BOARDS/${NAME}pnr.json



