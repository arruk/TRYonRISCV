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

	unsigned char result = 0;
	int x=0;
	while(x<10000) {
		top->a = (unsigned char)rand()%WORDSZ;
		top->b = (unsigned char)rand()%WORDSZ;
		top->cin = (unsigned char)rand()%2;

                top->eval();
                m_trace->dump(sim_time);
                sim_time++;

		result = (unsigned char)top->s;
		if(result != (unsigned char)(top->a + top->b + top->cin)) cout<<" A="<<(int)top->a<<" B="<<(int)top->b<<" cin="<<(int)top->cin<<" s="<<(int)top->s<<endl;
		else cout<<"succes"<<" A="<<(int)top->a<<" B="<<(int)top->b<<" cin="<<(int)top->cin<<" s="<<(int)top->s<<endl;
		x++;
	}
	m_trace->close();
	delete top;
	return 0;
}
