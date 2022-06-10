#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N_BLOCKS 10
#define MATRIX_SIZE 7
#define INPUT_MATRIX_SIZE 5
#define KERNEL_SIZE 3
#define OUTPUT_SIZE 7
#define N_ITERATIONS 100

 struct thread_data{
     int (*a_ptr)[MATRIX_SIZE];
     int (*b_ptr)[KERNEL_SIZE];
     int (*c_ptr)[OUTPUT_SIZE];
    };

void initialize_blocks(int a[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE], int b[N_BLOCKS][KERNEL_SIZE][KERNEL_SIZE]){
     for(int m = 0; m < N_BLOCKS; m++){
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                a[m][i][j] = rand() % 20;
            }
        }
        for (int i = 0; i < KERNEL_SIZE; ++i) {
            for (int j = 0; j < KERNEL_SIZE; ++j) {
                b[m][i][j] = rand() % 20;
            }
        }
    }
}

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

void * convolution(void * threadarg){;
     int (*my_a_ptr)[MATRIX_SIZE];
     int (*my_b_ptr)[KERNEL_SIZE];
     int (*my_c_ptr)[OUTPUT_SIZE];
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

    my_a_ptr = my_data -> a_ptr;
    my_b_ptr = my_data -> b_ptr;
    my_c_ptr = my_data -> c_ptr;

    int k_center_x = KERNEL_SIZE/2;
    int k_center_y = KERNEL_SIZE/2;
    int mm = 0;
    int nn = 0;
    int ii = 0;
    int jj = 0;
    int conv = 0;

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
                            conv += my_a_ptr[ii][jj] * my_b_ptr[mm][nn];
                        }
                    }
                }
                my_c_ptr[i][j] = conv;
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
     struct thread_data thread_args[N_BLOCKS];

    int my_a[N_BLOCKS][MATRIX_SIZE][MATRIX_SIZE] = {0};
    int my_b[N_BLOCKS][KERNEL_SIZE][KERNEL_SIZE] = {0};
    int my_c[N_BLOCKS][OUTPUT_SIZE][OUTPUT_SIZE] = {0};

    initialize_blocks(my_a, my_b);
    /*
    printf("displaying a(all batches):\n");
    display3D(my_a);*/
    
    pthread_t threads[N_BLOCKS];
    int iret1, iret2;

    for(int i = 0; i < N_ITERATIONS; i++){
        for(int n = 0; n < N_BLOCKS; n++){
            thread_args[n].a_ptr = *(my_a + n);
            thread_args[n].b_ptr = *(my_b + n);
            thread_args[n].c_ptr = *(my_c + n);

            pthread_create(&threads[n], NULL, convolution,  &thread_args[n]);
            pthread_join(*(threads+n), NULL);
        }
        /*
        printf("displaying c(all batches):\n");
        display3D(my_c);*/
        printf("finished %dth iteration\n\n", i);
    }
     printf("finished all %d iterations\n\n", N_ITERATIONS);
}

