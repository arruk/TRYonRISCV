#include "VSOC.h"
#include "verilated.h"
#include "femto_elf.h"
#include <iostream>


int main(int argc, char** argv, char** env) {
	VSOC top;
	top.CLK = 0;

	Elf32Info elf;
	int elf_status;

	// Call eval() so that readmemh()/initial bocks are executed
	// before anything else.
	top.eval();

	//char c='a';

	// Main simulation loop.
	while(!Verilated::gotFinish()) {
		top.CLK = !top.CLK;
		top.eval();
		//if(top.chg == 1){
		//	std::cout<<"write a char"<<std::endl;
		//	std::cin>>c;
		//	top.IO_mem_rdata = c;
		//}
	}
	return 0;
}
