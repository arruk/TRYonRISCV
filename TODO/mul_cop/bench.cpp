#include "VSOC.h"
#include "verilated.h"
#include "femto_elf.h"
#include <iostream>


int main(int argc, char** argv, char** env) {
	VSOC top;
	top.CLK = 0;
	top.RESETN = 1;

	Elf32Info elf;
	int elf_status;

	// Call eval() so that readmemh()/initial bocks are executed
	// before anything else.
	top.eval();

	top.pcpi_valid = 1;
	top.pcpi_insn = 0x22081B3;
	top.pcpi_rs1  = 0x0100010;
	top.pcpi_rs2  = 0x0100011;

	//char c='a';
	
	int counter =0;

	// Main simulation loop.
	while(!Verilated::gotFinish()) {
		top.CLK = !top.CLK;
		counter++;
		top.eval();
		printf("wr = %1d\nwait = %1d\nready = %1d\n", top.pcpi_wr, top.pcpi_wait, top.pcpi_ready);
		if(top.pcpi_ready){
			printf("result = %8X\ncycles = %d\n", top.pcpi_rd, counter);
			return 0;
		}
	}
	return 0;
}
