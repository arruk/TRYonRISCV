# Síntese na DE10S

cat ../../../SIM/PRECOMPILED/COREMARK/DATARAM.hex | tr [:blank:] [\\n] | awk 'NF'  > ./CMDATARAM.hex
paste -d" " numbershex CMDATARAM.hex > CMRAM.mif
sed -i s/$/\;/ CMRAM.mif
