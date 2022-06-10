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
void display2D(int result[MATRIX_SIZE][MATRIX_SIZE]){

   printf("\nMatrix 2D:\n");
   for (int i = 0; i < MATRIX_SIZE; ++i) {
      for (int j = 0; j < MATRIX_SIZE; ++j) {
         printf("%d  ", result[i][j]);
      }
      printf("\n");
   }
}

void toeplitz_convolution(int input_matrix[input_matrix_dim][input_matrix_dim], int filter[filter_dim][filter_dim], int output_matrix[MATRIX_SIZE][MATRIX_SIZE]){
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
     display2D(input_toeplitz_matrix);
     
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
     
    display2D(output_matrix);

 }

void reg_convolution(int input_matrix[input_matrix_dim][input_matrix_dim], int filter[filter_dim][filter_dim], int output_matrix[MATRIX_SIZE][MATRIX_SIZE]){
    int output_conv[overlap_dim][overlap_dim] = {{0}};
    //Iterate through input matrix overlaps
    for(int i = 0; i<overlap_dim; i++){
      for(int k = 0; k<overlap_dim; k++){
        int sum = 0;
        //Iterate through filter
        for(int j = 0; j<filter_dim; j++){
          for(int p=0; p<filter_dim; p++){
            //Set rows of toeplitz matrix
            sum += filter[j][p]*input_matrix[i+j][k+p];
          }
        }
        output_conv[i][k] = sum;
      }
    }
    
    //Serialize matrix
     int vec_i = 0;
     for(int j = 0;j < overlap_dim;j++){
         for(int p =0; p < overlap_dim; p++){
             output_matrix[vec_i][0] = output_conv[j][p];
             vec_i +=1;
         }
     }
    
    display2D(output_matrix);
} 

void compare(int toeplitz_conv[MATRIX_SIZE][MATRIX_SIZE], int reg_conv[MATRIX_SIZE][MATRIX_SIZE]){
    for(int x = 0; x < MATRIX_SIZE; x++){
        for(int y = 0; y < MATRIX_SIZE; y++){
            if(toeplitz_conv[x][y]!=reg_conv[x][y]){
                printf("Test failed!");
                return;
            }
        }
    }
    printf("Test passed!");
}
int main()
{
    int input_matrix[input_matrix_dim][input_matrix_dim] = {
                    {1,2,3},
                    {4,5,6},
                    {7,8,9}
                    };
    int filter[filter_dim][filter_dim] = {{1, 2},
                                          {3, 4}};
                                          
    
    int output_matrix[MATRIX_SIZE][MATRIX_SIZE] = {{0}};
    toeplitz_convolution(input_matrix, filter, output_matrix);
    int output_matrix_reg[MATRIX_SIZE][MATRIX_SIZE] = {{0}};
    reg_convolution(input_matrix, filter, output_matrix_reg);
    compare(output_matrix, output_matrix_reg);

    return 0;
}
