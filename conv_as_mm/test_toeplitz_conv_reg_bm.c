/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#define input_matrix_dim 3 
#define filter_dim 2
#define toeplitz_x_dim (input_matrix_dim - filter_dim + 1) * (input_matrix_dim - filter_dim + 1) 
#define toeplitz_y_dim filter_dim*filter_dim
#define overlap_dim input_matrix_dim - filter_dim + 1
#define MATRIX_SIZE 7
#define iterations 100

#include <stdlib.h>
void display2D(int result[MATRIX_SIZE][MATRIX_SIZE]){

   printf("\nMatrix 2D:\n");
   for (int i = 0; i < MATRIX_SIZE; ++i) {
      for (int j = 0; j < MATRIX_SIZE; ++j) {
         printf("%d  ", result[i][j]);
      }
      printf("\n");
   }
}

void toeplitz_convolution(int output_matrix[MATRIX_SIZE][MATRIX_SIZE]){
    //initialize matrices
    int input_matrix[input_matrix_dim][input_matrix_dim] = {{0}};
    int filter[filter_dim][filter_dim] = {{0}};

    for (int i = 0; i < input_matrix_dim; ++i) {
        for (int j = 0; j < input_matrix_dim; ++j) {
            input_matrix[i][j] = rand() % 20;
        }
    }
    for (int i = 0; i < filter_dim; ++i) {
        for (int j = 0; j < filter_dim; ++j) {
            filter[i][j] = rand() % 20;
        }
    }
    
     //int filter_vector[filter_dim*filter_dim];
     int filter_matrix[MATRIX_SIZE][MATRIX_SIZE] = {{0}};
     //int input_toeplitz[toeplitz_x_dim][toeplitz_y_dim] = {{0}};
     int input_toeplitz_matrix[MATRIX_SIZE][MATRIX_SIZE] = {{0}};
     
     //Serialize the filter
     int vec_i = 0;
     for(int j = 0;j < filter_dim;j++){
         for(int p =0; p < filter_dim; p++){
             //filter_vector[vec_i] = filter[j][p];
             filter_matrix[vec_i][0] = filter[j][p];
             vec_i +=1;
         }
     }

     //Iterate through input matrix overlaps
     int row = 0;
     for(int i = 0; i<overlap_dim; i++){
         for(int k = 0; k<overlap_dim; k++){
             int col = 0;
             //Iterate through filter
             for(int j = 0; j < filter_dim; j++){
                 for(int p = 0; p < filter_dim; p++){
                     //Set rows of toeplitz matrix
                     //input_toeplitz[row][col] = input_matrix[i+j][k+p];
                     input_toeplitz_matrix[row][col] = input_matrix[i+j][k+p];
                     col+=1;
                 }
             }
             row+=1;
         }
     }
     //display2D(input_toeplitz_matrix);
     
     //Matrix multiply
     for(int i = 0; i<MATRIX_SIZE; i++){
        for(int j = 0; j<MATRIX_SIZE; j++){
            int sum = 0;
            for(int y = 0; y<MATRIX_SIZE; y++){
              sum += input_toeplitz_matrix[i][y]*filter_matrix[y][j];
            }
            output_matrix[i][j] = sum;
        }
     }
     
    //display2D(output_matrix);

 }

int main()
{                                         
    for(int iter = 0; iter < iterations; iter++){
        int output_matrix[MATRIX_SIZE][MATRIX_SIZE] = {{0}};
        toeplitz_convolution(output_matrix);
        printf("finished %dth iteration\n\n", iter);
    }
    printf("finished all %d iterations\n", iterations);
    return 0;
}
