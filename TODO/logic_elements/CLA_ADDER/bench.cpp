#include "obj_dir/Vcla_adder.h"
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdint.h>
using namespace std;

#define WORDSZ 4294967295
#define CHARSZ 255
vluint64_t sim_time =0;

int main(int argc, char** argv, char** env) {
	Vcla_adder *top = new Vcla_adder;

	Verilated::traceEverOn(true);
	VerilatedVcdC *m_trace = new VerilatedVcdC;
	top->trace(m_trace, 5);
	m_trace->open("waveform.vcd");

	srand(time(0));

	uint32_t result = 0;
	int x=0;
	while(x<10) {
		top->a = 4294967295;//(uint32_t)rand()%WORDSZ;
		top->b = 1;//(uint32_t)rand()%WORDSZ;
		top->cin = 0;//(uint32_t)rand()%2;	
                
		top->eval();
                m_trace->dump(sim_time);
                sim_time++;

		result = (uint32_t)top->s;
		if(result != (uint32_t)(top->a + top->b + top->cin)) cout<<" A="<<top->a<<" B="<<top->b<<" cin="<<(int)top->cin<<" s="<<top->s<<endl;
		else cout<<"succes"<<endl<<" A="<<top->a<<" B="<<top->b<<" cin="<<(int)top->cin<<" s="<<top->s<<" cout = "<<(int)top->cout<<endl;
		x++;
	}
	m_trace->close();
	delete top;
	return 0;
}
