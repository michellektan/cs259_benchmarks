#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define MATRIX_SIZE 7
#define N_ITERATIONS 100
#define N_BLOCKS 10

 struct thread_data{
     int (*a_ptr)[MATRIX_SIZE];
     int (*b_ptr)[MATRIX_SIZE];
     int (*c_ptr)[MATRIX_SIZE];
    };

void display2D(int result[MATRIX_SIZE][MATRIX_SIZE]){

   printf("\nOutput 2D:\n");
   for (int i = 0; i < MATRIX_SIZE; ++i) {
      for (int j = 0; j < MATRIX_SIZE; ++j) {
         printf("%d  ", result[i][j]);
         if (j == MATRIX_SIZE-1)
            printf("\n");
      }
   }
}

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

void initialize_blocks(int a[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE], int b[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE]){
     for(int m = 0; m < N_BLOCKS; m++){
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                a[m][i][j] = rand() % 20;
                b[m][i][j] = rand() % 20;
            }
        }
    }
}

// same multiply function implemented in riscv
void * multiply(void * threadarg){;
     int (*my_a_ptr)[MATRIX_SIZE];
     int (*my_b_ptr)[MATRIX_SIZE];
     int (*my_c_ptr)[MATRIX_SIZE];
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

    my_a_ptr = my_data -> a_ptr;
    my_b_ptr = my_data -> b_ptr;
    my_c_ptr = my_data -> c_ptr;

        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                int sum = 0;
                for (int k = 0; k < MATRIX_SIZE; ++k) {
                    sum += my_a_ptr[i][k] * my_b_ptr[k][j];
                }
                my_c_ptr[i][j] = sum;
            }
        }
}

int main(){
    struct thread_data thread_args[N_BLOCKS];

    int my_a[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {0};
    int my_b[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {0};
    int my_c[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {0};

    initialize_blocks(my_a, my_b);
    
    printf("displaying a(all batches):\n");
    display3D(my_a);
    printf("displaying b(all batches):\n");
    display3D(my_b);
    
    pthread_t threads[N_BLOCKS];
    int iret1, iret2;

    for(int i = 0; i < N_ITERATIONS; i++){
        for(int n = 0; n < N_BLOCKS; n++){
            thread_args[n].a_ptr = *(my_a + n);
            thread_args[n].b_ptr = *(my_b + n);
            thread_args[n].c_ptr = *(my_c + n);

            pthread_create(&threads[n], NULL, multiply,  &thread_args[n]);
            pthread_join(*(threads+n), NULL);
        }
        
        printf("displaying c(all batches):\n");
        display3D(my_c);
        printf("finished %dth iteration\n\n", i);
    }
    printf("finished all %d iterations\n", N_ITERATIONS);
}

