map:	ula.v	
	verilator --trace --exe --build -cc bench.cpp ula.v
	./obj_dir/Vula

gtk:	waveform.vcd
	gtkwave waveform.vcd
	
exe:
	./obj_dir/Vula
