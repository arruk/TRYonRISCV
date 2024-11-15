
int array_a[3][3] = {2,2,2,
		     2,3,2,
		     2,2,2};

int array_b[3][3] = {3,3,3,
		     3,2,3,
		     3,3,3};

int main(){
	int array_c[3][3];

	for(int x=0; x<3; x++){
                for(int y=0; y<3; y++){
                	array_c[x][y] = 0;
		}
        }


	for(int x=0; x<3; x++){
		for(int y=0; y<3; y++){
			for(int z=0; z<3; z++){
				array_c[x][y] += array_a[x][z]*array_b[z][y];
			}
		}
	}


	for(int x=0; x<3; x++){
                for(int y=0; y<3; y++){
			printf("[%d]", array_c[x][y]);
		}
		printf("\n");
        }

}
