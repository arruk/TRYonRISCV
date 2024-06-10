#include "obj_dir/Vula.h"
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdint.h>
using namespace std;

#define WORDSZ 4294967295
vluint64_t sim_time =0;

int main(int argc, char** argv, char** env) {
	Vula *top = new Vula;

	Verilated::traceEverOn(true);
	VerilatedVcdC *m_trace = new VerilatedVcdC;
	top->trace(m_trace, 5);
	m_trace->open("waveform.vcd");

	srand(time(0));

	//int f3 [] = {0,1,4,5,6,7};
	//int f7 [] = {0,0,0,0,0,0};
	int f3 [] = {0,0,1,2,3,4,5,5,6,7};
	int f7 [] = {0,1,0,0,0,0,0,1,0,0};

	//top->op = 99;   // branch
	top->op = 51; // rtype

	int32_t result=0, take_b=0;
	int count=0, x=0, rtype=1;

	//while(x<(6*10000+1)) {
	while(x<(11*10000+1)) {
		top->in_a = (int32_t)rand()%WORDSZ;
		top->in_b = (int32_t)rand()%WORDSZ;
		if(f3[count] == 1 || f3[count] == 5) top->in_b = (uint32_t)top->in_b%32;
		//if(rand()%2) top->in_b = top->in_a;
		top->funct3 = f3[count];
		top->func7  = f7[count];
		
		top->eval();
		m_trace->dump(sim_time);
		sim_time++;

		//take_b = top->take_b;
		result = top->result;
		
		if(rtype) {
			switch(f3[count]) {
				case 0:
					if(f7[count]){
						if(result != (top->in_a - top->in_b)) cout<<"erro sub"<<" A="<<top->in_a<<" B="<<top->in_b<<" R="<<result<<endl;
					} else 
						if(result != (top->in_a + top->in_b)) cout<<"erro add"<<endl;
					break;
				case 1:
					if(result != (top->in_a << top->in_b)) cout<<"erro sll"<<" A="<<top->in_a<<" B="<<top->in_b<<" R="<<result<<endl;
					break;
				case 2:
					if(result != (top->in_a < top->in_b)) cout<<"erro slt"<<endl;
					break;
				case 3:   
					if(result != ((uint32_t)top->in_a < (uint32_t)top->in_b)) cout<<"erro sltu"<<endl;
					break;
				case 4:
					if(result != (top->in_a ^ top->in_b)) cout<<"erro xor"<<endl;
					break;
				case 5:
					if(f7[count]){
						if(result != (top->in_a >> top->in_b)) cout<<"erro sra"<<" A="<<top->in_a<<" B="<<top->in_b<<" R="<<result<<endl;
					} else 
						if(result != (top->in_a >> top->in_b)) cout<<"erro srl"<<" A="<<top->in_a<<" B="<<top->in_b<<" R="<<result<<endl;
					break;
				case 6:
					if(result != (top->in_a | top->in_b)) cout<<"erro or"<<endl;
					break;
				case 7:
					if(result != (top->in_a & top->in_b)) cout<<"erro and"<<endl;
					break;
			}
		} else {
			switch(f3[count]) {
				case 0:
					if(take_b != (top->in_a == top->in_b)) cout<<"erro beq"<<" A="<<top->in_a<<" B="<<top->in_b<<" R="<<take_b<<endl;
					break;
				case 1:
					if(take_b != (top->in_a != top->in_b)) cout<<"erro bne"<<endl;
					break;
				case 4:
					if(take_b != (top->in_a < top->in_b)) cout<<"erro blt"<<endl;
					break;
				case 5:
					if(take_b != (top->in_a >= top->in_b)) cout<<"erro bge"<<" A="<<top->in_a<<" B="<<top->in_b<<" R="<<take_b<<endl;
					break;
				case 6:
					if(take_b != ((uint32_t)top->in_a < (uint32_t)top->in_b)) cout<<"erro bltu"<<endl;
					break;
				case 7:
					if(take_b != ((uint32_t)top->in_a >= (uint32_t)top->in_b)) cout<<"erro bgeu"<<endl;
					break;
				default:
					break;
			}
		}

		//count = (count+1)%6;
		count = (count+1)%10;
		x++;
	}
	m_trace->close();
	delete top;
	return 0;
}
