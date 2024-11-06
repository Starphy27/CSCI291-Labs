#include<stdio.h>
#include <stdbool.h>

#define SIZE 24
#define nRows 8
#define nCols 3

// PROTOTYPES
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);
bool isValid(const int array[], int length, int pos);
void remove_element(int array[], int length, int pos);
void insert_element(int array[], int length, int pos, int value);
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]);

int main()
{
    int arr[SIZE];
    int arr2d[nRows][nCols];

    // Initialize arr with some values
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }

    // Initialize arr2d with some values
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            arr2d[i][j] = i * nCols + j;
        }
    }

    print_matrix(arr2d, nRows);

    // Call to different functions
    isValid(arr, SIZE, 7);
    remove_element(arr, SIZE, 7);
    print_array(arr, SIZE); // Check array after removal

    insert_element(arr, SIZE, 7, 100);
    print_array(arr, SIZE); // Check array after insertion

    reshape(arr, SIZE, nRows, nCols, arr2d);

    return 0;
}

void print_array(int array[], int length) {
    for (int i = 0; i < length; i++)
        printf("array[%d]= %d\n", i, array[i]);
}

void print_matrix(int mat[][nCols], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < nCols; j++)
            printf("mat[%d][%d]= %d\n", i, j, mat[i][j]);
        puts("");
    }
}

// Check if index is valid
bool isValid(const int array[], int length, int pos) {
    return (pos >= 0 && pos < length);
}

// Remove element at specified position
void remove_element(int array[], int length, int pos) {
    if (!isValid(array, length, pos)) {
        printf("Error: Invalid index %d\n", pos);
        return;
    }

    for (int i = pos; i < length - 1; i++)
        array[i] = array[i + 1];
    array[length - 1] = 0;  // Set last element to 0 after shifting
}

// Insert element at specified position (unchanged)
void insert_element(int array[], int length, int pos, int value) {
    if (!isValid(array, length, pos)) {
        printf("Invalid index\n");
        return;
    }

    for (int i = length - 1; i > pos; i--)
        array[i] = array[i - 1];
    array[pos] = value;
}

// Reshape 1D array into 2D array column by column
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Error: Array length does not match the specified dimensions.\n");
        return;
    }

    int k = 0;
    for (int j = 0; j < nCols; j++) {  // Iterate over columns first
        for (int i = 0; i < nRows; i++) {  // Then iterate over rows
            arr2d[i][j] = arr[k];
            k++;
        }
    }
    print_matrix(arr2d, nRows);  // Display the reshaped matrix
}