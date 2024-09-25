#include <stdio.h> // access to standard input/output library 

int main(void)
{
    float a = 0;
    printf("Enter the 1st number: ");
    scanf("%f", &a);

    float b = 0;
    printf("Enter the 2nd number: ");
    scanf("%f", &b);
    float product = a * b;
    printf("The product of %.3f and %.3f is %.3f\n", a, b, product);
return 0;
}
