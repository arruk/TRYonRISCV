#include<stdint.h>


int main(){
	
	printf("Hello from the OS!\n");
	return 0;

}

void p_exit(){

	printf("Bye from the OS!\n");

}

void exception(uint32_t c){

	printf("exception cautgh: ");
	switch(c){
		case 1:
			printf("Instruction access fault\n");
			break;
		case 2:
			printf("Illegal instruction\n");
			break;
		case 3:
			printf("Breakpoint\n");
			break;
		case 5:
			printf("Load access fault\n");
			break;
		case 7:
			printf("Store access fault\n");
			break;
		default:
			break;

	}
}
