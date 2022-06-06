#include <stdio.h>
#include <stdlib.h>
#define MATRIX_SIZE 7
#define N_ITERATIONS 100
#define N_BLOCKS 2

void display3D(int result[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE]){

   printf("\nOutput 3D:\n");
    for(int m = 0; m < N_BLOCKS; m++){
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                printf("%d  ", result[m][i][j]);
                if (j == MATRIX_SIZE-1)
                    printf("\n");
            }
        }
        printf("\n");
    }
}
// same multiply function implemented in riscv
void multiply(int c[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE]){;
    
    //initialize matrices a and b
    int a[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE];
    int b[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE];
    for(int m = 0; m < N_BLOCKS; m++){
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                a[m][i][j] = rand() % 20;
                b[m][i][j] = rand() % 20;
            }
        }
    }

    for (int m = 0; m < N_BLOCKS; m++){
        int (*pa)[MATRIX_SIZE] = a[m];
        int (*pb)[MATRIX_SIZE] = b[m];
        int (*pc)[MATRIX_SIZE] = c[m];
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                int sum = 0;
                for (int k = 0; k < MATRIX_SIZE; ++k) {
                    sum += pa[i][k] * pb[k][j];
                }
                pc[i][j] = sum;
            }
        }
    }
}

int main(){

    int my_c[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {0};

    for (int i = 0; i < N_ITERATIONS; i++){
        multiply(my_c);
    }
    printf("finished all iterations\n");
}
