BOARD=tangnano9k
FAMILY=GW1N-9C
DEVICE=GW1NR-LV9QN88PC6/I5

PROJ="SOC"
INFO_DIR="../INFO/BOARDS"
NAME=$(echo $1 | cut -d. -f 1 )

yosys -q -p "synth_gowin -noalu -nowidelut -top $PROJ -json BOARDS/$NAME.json" $1
nextpnr-himbaechel -l ${INFO_DIR}/${NAME}.txt --json BOARDS/${NAME}.json --write BOARDS/${NAME}pnr.json --device ${DEVICE} --vopt family=${FAMILY} --vopt cst=BOARDS/${BOARD}.cst
gowin_pack -d ${FAMILY} -o BOARDS/${NAME}.fs BOARDS/${NAME}pnr.json

