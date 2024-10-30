#include<stdio.h> 
#include <stdbool.h> 

#define SIZE 24
#define nRows 8
#define nCols 3

// PROTOTYPES
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);
bool isValid(int array[], int length);
void remove_element(int array[], int length, int index);
//void insert_element(int array[], int length, int index, int value);


int main()
{
    int arr[SIZE];
    int arr2d[nRows][nCols];
    print_matrix(arr2d,nRows);
    //Call to different functions
    isValid(arr, SIZE);
    //remove_element(arr, SIZE, 7);
    //insert_element(arr, SIZE, 7, 100);



    return 0;
}

void print_array(int array[], int length){
   for(int i=0;i<length; i++)
      printf("array[%d]= %d\n", i, array[i]);
}

void print_matrix(int mat[][nCols], int rows){
   for(int i=0;i<rows; i++){
    for(int j=0;j<nCols; j++)
         printf("mat[%d][%d]= %d\n", i,j, mat[i][j]);
    puts("");     
   }     
}

//FUNCTION DEFINITIONS

void insert_element(int array[], int length, int index, int value){
    if(index < 0 || index >= length){
        printf("Invalid index\n");
        return;
    }
    for(int i=length; i>index; i--)
        array[i] = array[i-1];
    array[index] = value;
}

void remove_element(int array[], int length, int index){
    if(index < 0 || index >= length){
        printf("Invalid index\n");
        return;
    }
    for(int i=index; i<length-1; i++)
        array[i] = array[i+1];
}



bool isValid(int array[], int length){
    for(int i=0; i<length; i++){
        if(array[i] < 0 || array[i] > 24)
            return false;
    }
    return true;
}
