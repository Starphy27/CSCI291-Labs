#include<iostream>
#include<iomanip>
#include <cstdlib> 
using namespace std;

// Implementation of print_real function
void print_real(float number, int fieldspace, int precision) {
    // Use fixed notation, set field width and precision, then print the number followed by a newline
    cout << fixed << setw(fieldspace) << setprecision(precision) << number << endl;
}

// Template function update_scale with default parameter
template <typename T>
void update_scale(T& m1, T& m2, T m3 = 10) {
    // Store original values before modification
    T orig_m1 = m1;
    T orig_m2 = m2;

    // Update m1: sum of original values multiplied by m3
    m1 = (orig_m1 + orig_m2) * m3;

    // Update m2: difference of original values multiplied by m3
    m2 = (orig_m1 - orig_m2) * m3;
}

int main(void) {
    float a, b;
    cout << " Please input two real numbers: ";
    cin >> a >> b;	

    // Print initial values
    print_real(a, 7, 3);
    print_real(b, 7, 3);

    // Call update_scale with a and b
    update_scale(a, b);

    // Print updated values
    print_real(a, 7, 3);
    print_real(b, 7, 3);
	
    return 0;
}