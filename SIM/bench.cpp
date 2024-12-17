#include "VSOC.h"
#include "verilated.h"
//#include "verilated_vcd_c.h"
#include "femto_elf.h"
#include <iostream>


//vluint64_t sim_time = 0;

int main(int argc, char** argv, char** env) {

	VSOC top;
	top.CLK = 0;

	Elf32Info elf;
	int elf_status;

	/*
	Verilated::traceEverOn(true);
	VerilatedVcdC *m_trace = new VerilatedVcdC;
	top.trace(m_trace, 99);
	m_trace->open("wf.vcd");
	*/

	// Call eval() so that readmemh()/initial bocks are executed
	// before anything else.
	top.eval();

	//char c='a';

	// Main simulation loop.
	while(!Verilated::gotFinish()) {
		top.CLK = !top.CLK;
		top.eval();
		
		//m_trace->dump(sim_time);
		//sim_time++;
		
		//if(top.chg == 1){
		//	std::cout<<"write a char"<<std::endl;
		//	std::cin>>c;
		//	top.IO_mem_rdata = c;
		//}
	}
	//m_trace->close();
	return 0;
}
