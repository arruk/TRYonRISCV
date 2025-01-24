open_project PRIMER25k.gprj
set_option -use_cpu_as_gpio 1
set_file_enable src/soc.v true
set_file_enable src/alu.v true
set_file_enable src/uart_tx.v true
set_file_enable src/clockworks.v true
set_file_enable src/mem.sv true
set_file_enable src/core.sv true
set_file_enable src/soc.cst true
set_file_enable src/DATARAM.hex true
set_file_enable src/PROGROM.hex true
set_file_enable src/GWDATARAM.hex true
run syn
run pnr
run close
