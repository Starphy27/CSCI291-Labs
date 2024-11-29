#include<iostream> // Include input/output stream library 
#include<iomanip>  // Include library for manipulating output format 
#include <cstdlib> // Include library for general utilities 
using namespace std; // Use the standard namespace to simplify code (

// Function to print a real (floating-point) number 
void print_real(float number, int fieldspace, int precision) {
    // Set output format to fixed-point notation 
    // setw(fieldspace) sets the minimum field width of the output
    // setprecision(precision) sets the number of digits to display after the decimal point
    cout << fixed << setw(fieldspace) << setprecision(precision) << number << endl;
}

// Template function to update the values of two variables (m1 and m2) based on a formula
// Accepts reference parameters (T& m1, T& m2) so the changes affect the original arguments
// m3 is a default parameter with a value of 10 (if not provided, it defaults to 10)
template <typename T>
void update_scale(T& m1, T& m2, T m3 = 10) {
    // Store the original values of m1 and m2 for later calculations
    T orig_m1 = m1;
    T orig_m2 = m2;

    // Update m1: calculate the sum of the original values, then multiply by m3
    m1 = (orig_m1 + orig_m2) * m3;

    // Update m2: calculate the difference of the original values, then multiply by m3
    m2 = (orig_m1 - orig_m2) * m3;
}

// Main function: Entry point of the program
int main(void) {
    float a, b; // Declare two floating-point variables to store user input
    cout << " Please input two real numbers: "; // Prompt the user for input
    cin >> a >> b; // Read two floating-point numbers from the user and store in a and b	

    // Print the initial values of a and b with 7 spaces width and 3 digits precision
    print_real(a, 7, 3);
    print_real(b, 7, 3);

    // Call the update_scale function with a and b to modify their values
    update_scale(a, b);

    // Print the updated values of a and b with the same formatting
    print_real(a, 7, 3);
    print_real(b, 7, 3);
	
    return 0; // Return 0 to indicate successful execution
}
