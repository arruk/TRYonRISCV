#include "csr.h"

int main(){

	uint32_t mepc  = 0x341;	
	uint32_t mtvec = 0x305;

	uint32_t res = csrrw((uint32_t)30, mepc);
	printf("res = %d\n", (int)res);
	
	res = csrrw((uint32_t)20, mepc);
	printf("res mepc = %d\n", (int)res);

	res = csrrw((uint32_t)20, mtvec);
	printf("res mepc = %d\n", (int)res);
	
	res = csrrw((uint32_t)15, mtvec);
	printf("res mtvec = %d\n", (int)res);
	
}
