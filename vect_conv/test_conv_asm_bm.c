#include <stdio.h>
#include <stdlib.h>

#define N_BLOCKS 10
#define MATRIX_SIZE 7
#define KERNEL_SIZE 3
#define OUTPUT_SIZE 7
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

// function to display the matrix
void display(int result[MATRIX_SIZE][MATRIX_SIZE]){

   printf("\nOutput Matrix:\n");
   for (int i = 0; i < MATRIX_SIZE; ++i) {
      for (int j = 0; j < MATRIX_SIZE; ++j) {
         printf("%d  ", result[i][j]);
         if (j == MATRIX_SIZE-1)
            printf("\n");
      }
   }
}

int main(){
    int my_a[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {0};
    int my_b[N_BLOCKS][KERNEL_SIZE][KERNEL_SIZE] = {0};
    int my_c[N_BLOCKS][OUTPUT_SIZE][OUTPUT_SIZE] = {0};
    register int tmp_c;
    register int tmp_b;
    register int tmp_a;

     __asm__ volatile("m_st %[tmp_c], 0(%[c])\n\t"
                   :
                   : [c] "r"(my_c[0][0]), [tmp_c] "r"(tmp_c));

    for (int m = 0; m < N_BLOCKS; m++) {
        // Load the output.
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                my_a[m][i][j] = rand() % 20;
            }
        }
        for (int i = 0; i < KERNEL_SIZE; ++i) {
            for (int j = 0; j < KERNEL_SIZE; ++j) {
                my_b[m][i][j] = rand() % 20;
            }
        }
    }

 #pragma GCC unroll 0
 for(int i = 0; i < N_ITERATIONS; i++){
    for (int m = 0; m < N_BLOCKS; m++){
        int (*pa)[MATRIX_SIZE] = my_a[m];
        int (*pb)[KERNEL_SIZE] = my_b[m];
        int (*pc)[OUTPUT_SIZE] = my_c[m];
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
    printf("finished %dth iteration\n\n", i);
 }
    printf("finished all %d iterations\n", N_ITERATIONS);
}