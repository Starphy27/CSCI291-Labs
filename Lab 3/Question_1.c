#include <stdio.h>
#include <stdbool.h>

#define SIZE 24

// FUNCTION PROTOTYPES
bool isValid(const int array[], int length, int pos);
void remove_element(int array[], int length, int pos);
void insert_element(int array[], int length, int pos, int value);
void reshape(const int array[], int length, int nRows, int nCols, int array_2d[nRows][nCols]);
void trans_matrix(int nRows, int nCols, int mat2[nCols][nRows], const int mat[nRows][nCols]);
bool found_duplicate(const int array[], int length);

int main()
{
    int arr[SIZE] = {0};  // Initialize array to avoid undefined behavior
    int length = 6;
    int Eg_Array[6] = {10, 20, 30, 40, 50, 60};

    // TESTING: remove_element 
    printf("An example array: \n");
    for (int i = 0; i < length; i++) {
        printf("%d ", Eg_Array[i]);
    }
    printf("\n");
    
    remove_element(Eg_Array, length, 3);
    printf("After removing element at index 3: ");
    for (int i = 0; i < length - 1; i++) {
        printf("%d ", Eg_Array[i]);
    }
    printf("\n");

    // TESTING: insert_element
    insert_element(Eg_Array, length, 3, 45); 
    printf("After inserting 45 at index 3: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", Eg_Array[i]);
    }
    printf("\n");

    // TESTING: reshape  
    int oneD[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};  
    int nRows = 4, nCols = 3;
    int twoD[4][3];
    
    reshape(oneD, 12, nRows, nCols, twoD);
    printf("2D array (filled column by column): \n");
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            printf("%d ", twoD[i][j]);
        }
        printf("\n");
    }

   // TESTING: trans_matrix
   int mat[4][3] = 
   {
       {1, 2, 3},
       {4, 5, 6},
       {7, 8, 9},
       {10, 11, 12}
   };
   int mat2[3][4];
   trans_matrix(4, 3, mat2, mat);
   printf("Transposed matrix: \n");
   for (int i = 0; i < 3; i++) 
   {
       for (int j = 0; j < 4; j++) 
       {
           printf("%d ", mat2[i][j]);
       }
       printf("\n");
   }

   // TESTING: found_duplicate
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    bool hasDuplicate = found_duplicate(arr2, 12);
    printf("Array has duplicates: %s\n", hasDuplicate ? "true" : "false");

    // Call to different functions
    if (isValid(arr, SIZE, 7)) {
        insert_element(arr, SIZE, 7, 100);
    }

    return 0;
}


// FUNCTION DEFINITIONS 

// Check if index is valid (within the array bounds)
bool isValid(const int array[], int length, int pos) {
    return (pos >= 0 && pos < length);
}  

// Remove element at specified position
void remove_element(int array[], int length, int pos) {
    if (!isValid(array, length, pos)) {
        printf("Error: Invalid index %d\n", pos);
        return;
    }

    for (int i = pos; i < length - 1; i++) { // 
        array[i] = array[i + 1]; 
    }
    array[length - 1] = 0;  // Set last element to 0 after shifting
}

// Insert element at specified position
void insert_element(int array[], int length, int pos, int value) {
    if (!isValid(array, length - 1, pos)) {
        printf("Invalid position\n");
        return;
    }
    
    for (int i = length - 1; i > pos; i--) {
        array[i] = array[i - 1];
    }
    array[pos] = value;
}    

// Changes a 1D array into a 2D array by filling it column by column
void reshape(const int array[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    if (length != (nRows * nCols)) {
        printf("Invalid input: length must equal nRows * nCols\n");
        return;
    }

    int k = 0;
    for (int j = 0; j < nCols; j++) {         // Outer loop iterates through columns
        for (int i = 0; i < nRows; i++) {     // Inner loop iterates through rows
            arr2d[i][j] = array[k++];
        }
    }
}

// Transpose of the input matrix mat 
void trans_matrix(int nRows, int nCols, int mat2[nCols][nRows], const int mat[nRows][nCols]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat2[j][i] = mat[i][j];
        }
    }
}

// Checks if there are duplicates
bool found_duplicate(const int array[], int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (array[i] == array[j]) {
                return true;
            }
        }
    }
    return false;
}