#include <stdio.h>
#define N_BLOCKS 10
#define MATRIX_SIZE 7
#define KERNEL_SIZE 3
#define OUTPUT_SIZE 7
#define N_ITERATIONS 1

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

void convolution(int input[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE], int kernel[N_BLOCKS][KERNEL_SIZE][KERNEL_SIZE], int output[N_BLOCKS][OUTPUT_SIZE][OUTPUT_SIZE]){;
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
    //input matrix (7x7)
     int my_a[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {
                        {{0, 0, 0, 0, 0, 0, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 2, 1, 3, 4, 4, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 0, 0, 0, 0, 0, 0}},
                         {{0, 0, 0, 0, 0, 0, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 2, 1, 3, 4, 4, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 0, 0, 0, 0, 0, 0}},
                         {{0, 0, 0, 0, 0, 0, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 2, 1, 3, 4, 4, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 0, 0, 0, 0, 0, 0}},
                         {{0, 0, 0, 0, 0, 0, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 2, 1, 3, 4, 4, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 0, 0, 0, 0, 0, 0}},
                         {{0, 0, 0, 0, 0, 0, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 2, 1, 3, 4, 4, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 0, 0, 0, 0, 0, 0}},
                         {{0, 0, 0, 0, 0, 0, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 2, 1, 3, 4, 4, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 0, 0, 0, 0, 0, 0}},
                         {{0, 0, 0, 0, 0, 0, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 2, 1, 3, 4, 4, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 0, 0, 0, 0, 0, 0}},
                         {{0, 0, 0, 0, 0, 0, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 2, 1, 3, 4, 4, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 0, 0, 0, 0, 0, 0}},
                         {{0, 0, 0, 0, 0, 0, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 2, 1, 3, 4, 4, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 0, 0, 0, 0, 0, 0}},
                         {{0, 0, 0, 0, 0, 0, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 2, 1, 3, 4, 4, 0},
                        {0, 4, 5, 3, 5, 6, 0},
                        {0, 6, 1, 2, 5, 7, 0},
                        {0, 0, 0, 0, 0, 0, 0}}
    };
    int my_b[N_BLOCKS][KERNEL_SIZE][KERNEL_SIZE] = {
                        {{2, 1, 3},
                         {1, 3, 4},
                         {1, 4, 5}},
                         {{2, 1, 3},
                         {1, 3, 4},
                         {1, 4, 5}},
                           {{2, 1, 3},
                         {1, 3, 4},
                         {1, 4, 5}},
                         {{2, 1, 3},
                         {1, 3, 4},
                         {1, 4, 5}},
                           {{2, 1, 3},
                         {1, 3, 4},
                         {1, 4, 5}},
                         {{2, 1, 3},
                         {1, 3, 4},
                         {1, 4, 5}},
                           {{2, 1, 3},
                         {1, 3, 4},
                         {1, 4, 5}},
                         {{2, 1, 3},
                         {1, 3, 4},
                         {1, 4, 5}},
                           {{2, 1, 3},
                         {1, 3, 4},
                         {1, 4, 5}},
                         {{2, 1, 3},
                         {1, 3, 4},
                         {1, 4, 5}}
    };

    int correct_matrix[N_BLOCKS][OUTPUT_SIZE][OUTPUT_SIZE] = {
                        {{8, 14, 23, 28, 26, 21, 18},
                        {16, 25, 57, 49, 58, 60, 45},
                        {14, 44, 85, 71, 92, 106, 70},
                        {16, 46, 73, 63, 91, 102, 69},
                        {18, 34, 74, 70, 93, 96, 65},
                        {10, 40, 72, 57, 71, 90, 58},
                        {6, 25, 36, 18, 37, 53, 35}},
                        {{8, 14, 23, 28, 26, 21, 18},
                        {16, 25, 57, 49, 58, 60, 45},
                        {14, 44, 85, 71, 92, 106, 70},
                        {16, 46, 73, 63, 91, 102, 69},
                        {18, 34, 74, 70, 93, 96, 65},
                        {10, 40, 72, 57, 71, 90, 58},
                        {6, 25, 36, 18, 37, 53, 35}},
                         {{8, 14, 23, 28, 26, 21, 18},
                        {16, 25, 57, 49, 58, 60, 45},
                        {14, 44, 85, 71, 92, 106, 70},
                        {16, 46, 73, 63, 91, 102, 69},
                        {18, 34, 74, 70, 93, 96, 65},
                        {10, 40, 72, 57, 71, 90, 58},
                        {6, 25, 36, 18, 37, 53, 35}},
                        {{8, 14, 23, 28, 26, 21, 18},
                        {16, 25, 57, 49, 58, 60, 45},
                        {14, 44, 85, 71, 92, 106, 70},
                        {16, 46, 73, 63, 91, 102, 69},
                        {18, 34, 74, 70, 93, 96, 65},
                        {10, 40, 72, 57, 71, 90, 58},
                        {6, 25, 36, 18, 37, 53, 35}},
                         {{8, 14, 23, 28, 26, 21, 18},
                        {16, 25, 57, 49, 58, 60, 45},
                        {14, 44, 85, 71, 92, 106, 70},
                        {16, 46, 73, 63, 91, 102, 69},
                        {18, 34, 74, 70, 93, 96, 65},
                        {10, 40, 72, 57, 71, 90, 58},
                        {6, 25, 36, 18, 37, 53, 35}},
                        {{8, 14, 23, 28, 26, 21, 18},
                        {16, 25, 57, 49, 58, 60, 45},
                        {14, 44, 85, 71, 92, 106, 70},
                        {16, 46, 73, 63, 91, 102, 69},
                        {18, 34, 74, 70, 93, 96, 65},
                        {10, 40, 72, 57, 71, 90, 58},
                        {6, 25, 36, 18, 37, 53, 35}},
                         {{8, 14, 23, 28, 26, 21, 18},
                        {16, 25, 57, 49, 58, 60, 45},
                        {14, 44, 85, 71, 92, 106, 70},
                        {16, 46, 73, 63, 91, 102, 69},
                        {18, 34, 74, 70, 93, 96, 65},
                        {10, 40, 72, 57, 71, 90, 58},
                        {6, 25, 36, 18, 37, 53, 35}},
                        {{8, 14, 23, 28, 26, 21, 18},
                        {16, 25, 57, 49, 58, 60, 45},
                        {14, 44, 85, 71, 92, 106, 70},
                        {16, 46, 73, 63, 91, 102, 69},
                        {18, 34, 74, 70, 93, 96, 65},
                        {10, 40, 72, 57, 71, 90, 58},
                        {6, 25, 36, 18, 37, 53, 35}},
                         {{8, 14, 23, 28, 26, 21, 18},
                        {16, 25, 57, 49, 58, 60, 45},
                        {14, 44, 85, 71, 92, 106, 70},
                        {16, 46, 73, 63, 91, 102, 69},
                        {18, 34, 74, 70, 93, 96, 65},
                        {10, 40, 72, 57, 71, 90, 58},
                        {6, 25, 36, 18, 37, 53, 35}},
                        {{8, 14, 23, 28, 26, 21, 18},
                        {16, 25, 57, 49, 58, 60, 45},
                        {14, 44, 85, 71, 92, 106, 70},
                        {16, 46, 73, 63, 91, 102, 69},
                        {18, 34, 74, 70, 93, 96, 65},
                        {10, 40, 72, 57, 71, 90, 58},
                        {6, 25, 36, 18, 37, 53, 35}}

    };

    //output matrix (11x11)
    int my_c[N_BLOCKS][OUTPUT_SIZE][OUTPUT_SIZE] = {0};
 
   register int tmp_c;
    register int tmp_b;
    register int tmp_a;

     __asm__ volatile("m_st %[tmp_c], 0(%[c])\n\t"
                   :
                   : [c] "r"(my_c[0][0]), [tmp_c] "r"(tmp_c));

    int (*pa)[MATRIX_SIZE][MATRIX_SIZE] = my_a;
    int (*pb)[KERNEL_SIZE][KERNEL_SIZE] = my_b;
    int (*pc)[OUTPUT_SIZE][OUTPUT_SIZE] = my_c;

    #pragma GCC unroll 0
        for (int m = 0; m < N_ITERATIONS; m++) {
        // Load the output.
            __asm__ volatile("m_ld_l %[tmp_a], 0(%[a])\n\t"
                            "m_ld_r %[tmp_b], 0(%[b])\n\t"
                            "m_mult %[tmp_c], %[tmp_a], %[tmp_b]\n\t"
                            : [tmp_c] "=&r"(tmp_c), [tmp_a] "=r"(tmp_a),
                            [tmp_b] "=r"(tmp_b)
                            : [a] "r"(pa), [b] "r"(pb));
        __asm__ volatile("m_st %[tmp_c], 0(%[c])\n\t"
                        :
                        : [c] "r"(pc), [tmp_c] "r"(tmp_c));
        }

    //display3D(my_c);
    compare(correct_matrix, my_c);
}

