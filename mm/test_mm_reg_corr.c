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

// same multiply function implemented in riscv
void multiply(int a[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE], int b[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE], int c[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE]){;
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

//second implementation
void multiply2(int a[N_BLOCKS][4][4], int b[N_BLOCKS][4][4], int c[N_BLOCKS][4][4]){;
    for (int m = 0; m < N_BLOCKS; m++){
        int (*pa)[4] = a[m];
        int (*pb)[4] = b[m];
        int (*pc)[4] = c[m];
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                pc[i][j] = 0;
                for (int k = 0; k < 4; ++k) {
                    pc[i][j] += (pa[i][k] * pb[k][j]);
                }
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
                        {{42, 63, 33, 40, 73, 90, 110},
                        {82, 123, 68, 80, 143, 175, 215},
                        {79, 114, 77, 81, 141, 170, 209},
                        {66, 77, 54, 60, 106, 127, 156},
                        {82, 123, 68, 80, 143, 175, 215},
                        {79, 114, 77, 81, 141, 170, 209},
                        {66, 77, 54, 60, 106, 127, 156}},
                        {{42, 63, 33, 40, 73, 90, 110},
                        {82, 123, 68, 80, 143, 175, 215},
                        {79, 114, 77, 81, 141, 170, 209},
                        {66, 77, 54, 60, 106, 127, 156},
                        {82, 123, 68, 80, 143, 175, 215},
                        {79, 114, 77, 81, 141, 170, 209},
                        {66, 77, 54, 60, 106, 127, 156}}

    };

    int my_c[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {0};

    for (int i = 0; i < 10; i++){
        multiply(my_a, my_b, my_c);
    }
    display3D(my_c);
    compare(correct_matrix, my_c);
}
