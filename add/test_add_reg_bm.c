#include <stdio.h>
#include <stdlib.h>
#define MATRIX_SIZE 7
#define N_BLOCKS 1
#define N_ITERATIONS 100

// function to display the matrix
void display3D(int result[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE]){
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
void add(int c[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE]){;
    
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
    
    printf("displaying A: \n");
    display3D(a);
    printf("displaying B: \n");
    display3D(b);
    
    for (int m = 0; m < N_BLOCKS; m++){
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

    int my_c[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {0};

    for (int i = 0; i < N_ITERATIONS; i++){
        add(my_c);
        printf("finished %dth iteration\n\n", i);
    }
    printf("finished all %d iterations\n", N_ITERATIONS);
}
