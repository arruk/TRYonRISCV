
#include "LIB/perf.h"

int array_a[3][3] = {2,2,2,
		     2,3,2,
		     2,2,2};

int array_b[3][3] = {3,3,3,
		     3,2,3,
		     3,3,3};

/*void zera(int **array_c){

	for(int x=0; x<3; x++){
                for(int y=0; y<3; y++){
                        array_c[x][y] = 0;
                }
        }

}

void calcula(int **array_c) {
        for(int x=0; x<3; x++){
                for(int y=0; y<3; y++){
                        for(int z=0; z<3; z++){
                                array_c[x][y] += array_a[x][z]*array_b[z][y];
                        }
                }
        }
}

void mostra (int **array_c) {
        for(int x=0; x<3; x++){
                for(int y=0; y<3; y++){
                        printf("[%d]", array_c[x][y]);
                }
                printf("\n");
        }	
}*/


int main(){
	int array_c[3][3];

	//zera(array_c);
	
	for(int x=0; x<3; x++){
                for(int y=0; y<3; y++){
                	array_c[x][y] = 0;
		}
        }
	

	//calcula(array_c);
	for(int x=0; x<3; x++){
		for(int y=0; y<3; y++){
			for(int z=0; z<3; z++){
				array_c[x][y] += array_a[x][z]*array_b[z][y];
			}
		}
	}

	//mostra(array_c);
	for(int x=0; x<3; x++){
                for(int y=0; y<3; y++){
			printf("[%d]", array_c[x][y]);
		}
		printf("\n");
        }
	
	uint64_t instret = rdinstret();
	uint64_t cycles = rdcycle();
	printf("cycles=%d     instret=%d    100CPI=%d\n", (int)cycles, (int)instret, (int)(100*cycles/instret));
}
