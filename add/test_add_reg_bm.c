#include <stdio.h>
#include <stdlib.h>
#define MATRIX_SIZE 7
#define N_ITERATIONS 1000

// same multiply function implemented in riscv
void add(int c[N_ITERATIONS][MATRIX_SIZE][MATRIX_SIZE]){;
    
    //initialize matrices a and b
    int a[N_ITERATIONS][MATRIX_SIZE][MATRIX_SIZE];
    int b[N_ITERATIONS][MATRIX_SIZE][MATRIX_SIZE];
    for(int m = 0; m < N_ITERATIONS; m++){
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                a[m][i][j] = rand() % 20;
                b[m][i][j] = rand() % 20;
            }
        }
    }
    
    for (int m = 0; m < N_ITERATIONS; m++){
        int (*pa)[MATRIX_SIZE] = a[m];
        int (*pb)[MATRIX_SIZE] = b[m];
        int (*pc)[MATRIX_SIZE] = c[m];
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                pc[i][j] = pa[i][j] + pb[i][j];
            }
        }
    }
}

int main(){

    int my_c[N_ITERATIONS][MATRIX_SIZE][MATRIX_SIZE] = {0};

    for (int i = 0; i < N_ITERATIONS; i++){
        add(my_c);
    }
    printf("finished 1000 iterations\n");
}
