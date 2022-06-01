#include <stdio.h>
#include <stdlib.h>

#define N_BLOCKS 2
#define N_ITERATIONS 1000
#define MATRIX_SIZE 7
#define INPUT_MATRIX_SIZE 5
#define KERNEL_SIZE 3
#define OUTPUT_SIZE 7

// function to display the matrix
void display3D(int result[N_BLOCKS][OUTPUT_SIZE][OUTPUT_SIZE]){

   printf("\nOutput 3D:\n");
    for(int m = 0; m < N_BLOCKS; m++){
        for (int i = 0; i < OUTPUT_SIZE; ++i) {
            for (int j = 0; j < OUTPUT_SIZE; ++j) {
                printf("%d  ", result[m][i][j]);
                if (j == OUTPUT_SIZE-1)
                    printf("\n");
            }
        }
        printf("\n");
    }
}

void convolution(int output[N_BLOCKS][OUTPUT_SIZE][OUTPUT_SIZE]){;
    //initialize matrices a and b
    int input[N_ITERATIONS][MATRIX_SIZE][MATRIX_SIZE];
    int kernel[N_ITERATIONS][KERNEL_SIZE][KERNEL_SIZE];
    for(int m = 0; m < N_ITERATIONS; m++){
        for (int i = 1; i < MATRIX_SIZE - 1; ++i) {
            for (int j = 1; j < MATRIX_SIZE - 1; ++j) {
                input[m][i][j] = rand() % 20;
            }
        }

        for (int i = 0; i < KERNEL_SIZE; ++i) {
            for (int j = 0; j < KERNEL_SIZE; ++j) {
                kernel[m][i][j] = rand() % 20;
            }
        }
    }
    
    
    int k_center_x = KERNEL_SIZE/2;
    int k_center_y = KERNEL_SIZE/2;
    int mm = 0;
    int nn = 0;
    int ii = 0;
    int jj = 0;
    int conv = 0;
    for (int m = 0; m < N_BLOCKS; m++){
        int (*p_input)[MATRIX_SIZE] = input[m];
        int (*p_kernel)[KERNEL_SIZE] = kernel[m];
        int (*p_output)[OUTPUT_SIZE] = output[m];
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                conv = 0;
                for(int m = 0; m < KERNEL_SIZE; m++){
                    mm = KERNEL_SIZE - 1 - m;
                    for(int n = 0; n < KERNEL_SIZE; n++){
                        nn = KERNEL_SIZE - 1 - n;
                        ii = i + (k_center_y - mm);
                        jj = j + (k_center_x - nn);
                        if(ii >= 0 && ii < MATRIX_SIZE && jj >= 0 && jj < MATRIX_SIZE){
                            conv += p_input[ii][jj] * p_kernel[mm][nn];
                        }
                    }
                }
                p_output[i][j] = conv;
            }
        }
    }
}


void compare(int correct_matrix[N_BLOCKS][OUTPUT_SIZE][OUTPUT_SIZE], int test_matrix[N_BLOCKS][OUTPUT_SIZE][OUTPUT_SIZE]){
    int test_num = 0;
    for (int m = 0; m < N_BLOCKS; m++){
        for (int i = 0; i < OUTPUT_SIZE; ++i) {
            for (int j = 0; j < OUTPUT_SIZE; ++j) {
                if (correct_matrix[m][i][j] != test_matrix[m][i][j]){
                        printf("test %d failed\n", test_num);
                        return;
                }
            }
        }
        test_num++;
        printf("test %d passed\n", test_num);
    }  
    printf("Correct matrices for all tests\n");
}

int main(){

    int my_output[N_BLOCKS][OUTPUT_SIZE][OUTPUT_SIZE] = {0};

    for (int i = 0; i < N_ITERATIONS; i++){
        convolution(my_output);
    }
        printf("finished 1000 iterations\n");
}

