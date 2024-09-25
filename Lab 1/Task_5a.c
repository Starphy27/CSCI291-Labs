#include <stdio.h> // access to standard input/output library 


int main(void)
{
    int a = 0;
    printf("Enter the 1st number: ");
    scanf("%d", &a);

    int b = 0;
    printf("Enter the 2nd number: ");
    scanf("%d", &b);
    int sum = a + b;
    printf("The sum of %d and %d is %d\n", a, b, sum);
return 0;
}
