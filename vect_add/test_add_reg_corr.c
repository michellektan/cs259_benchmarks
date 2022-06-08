#include <stdio.h>
#define N_BLOCKS 2
#define MATRIX_SIZE 7

void display2D(int result[MATRIX_SIZE][MATRIX_SIZE]){

   printf("\nOutput 2D:\n");
   for (int i = 0; i < MATRIX_SIZE; ++i) {
      for (int j = 0; j < MATRIX_SIZE; ++j) {
         printf("%d  ", result[i][j]);
         if (j == 3)
            printf("\n");
      }
   }
}

// function to display the matrix
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

// same add function implemented in riscv
void add(int a[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE], int b[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE], int c[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE]){;
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

void compare(int correct_matrix[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE], int test_matrix[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE]){
    int test_num = 0;
    for (int m = 0; m < N_BLOCKS; m++){
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
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
   int my_a[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {
                        {{1, 1, 2, 1, 3, 4, 4},
                        {1, 4, 5, 3, 5, 6, 7},
                        {2, 6, 1, 2, 5, 7, 8},
                        {5, 2, 1, 3, 4, 4, 6},
                        {1, 4, 5, 3, 5, 6, 7},
                        {2, 6, 1, 2, 5, 7, 8},
                        {5, 2, 1, 3, 4, 4, 6}},
                         {{1, 1, 2, 1, 3, 4, 4},
                        {1, 4, 5, 3, 5, 6, 7},
                        {2, 6, 1, 2, 5, 7, 8},
                        {5, 2, 1, 3, 4, 4, 6},
                        {1, 4, 5, 3, 5, 6, 7},
                        {2, 6, 1, 2, 5, 7, 8},
                        {5, 2, 1, 3, 4, 4, 6}}
    };
    int my_b[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {
                        {{1, 1, 2, 1, 3, 4, 4},
                        {1, 4, 5, 3, 5, 6, 7},
                        {2, 6, 1, 2, 5, 7, 8},
                        {5, 2, 1, 3, 4, 4, 6},
                        {1, 4, 5, 3, 5, 6, 7},
                        {2, 6, 1, 2, 5, 7, 8},
                        {5, 2, 1, 3, 4, 4, 6}},
                         {{1, 1, 2, 1, 3, 4, 4},
                        {1, 4, 5, 3, 5, 6, 7},
                        {2, 6, 1, 2, 5, 7, 8},
                        {5, 2, 1, 3, 4, 4, 6},
                        {1, 4, 5, 3, 5, 6, 7},
                        {2, 6, 1, 2, 5, 7, 8},
                        {5, 2, 1, 3, 4, 4, 6}}
    };

    int correct_matrix[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {
                        {{2, 2, 4, 2, 6, 8, 8},
                        {2, 8, 10, 6, 10, 12, 14},
                        {4, 12, 2, 4, 10, 14, 16},
                        {10, 4, 2, 6, 8, 8, 12},
                        {2, 8, 10, 6, 10, 12, 14},
                        {4, 12, 2, 4, 10, 14, 16},
                        {10, 4, 2, 6, 8, 8, 12}},
                        {{2, 2, 4, 2, 6, 8, 8},
                        {2, 8, 10, 6, 10, 12, 14},
                        {4, 12, 2, 4, 10, 14, 16},
                        {10, 4, 2, 6, 8, 8, 12},
                        {2, 8, 10, 6, 10, 12, 14},
                        {4, 12, 2, 4, 10, 14, 16},
                        {10, 4, 2, 6, 8, 8, 12}}
    };

    int my_c[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {0};

    for (int i = 0; i < 10; i++){
        add(my_a, my_b, my_c);
    }
    display3D(my_c);
    compare(correct_matrix, my_c);
}
