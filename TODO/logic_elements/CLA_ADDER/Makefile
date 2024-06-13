map:	cla_adder.v	
	verilator --trace --exe --build -cc bench.cpp cla_adder.v
	./obj_dir/Vcla_adder

gtk:	waveform.vcd
	gtkwave waveform.vcd
	
exe:
	./obj_dir/Vcla_adder
