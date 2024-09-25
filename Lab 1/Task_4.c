#include <stdio.h> // access to standard input/output library 
#define  convertor (1.82) // definition of a constant 
int main(void)
{
float cels; // celsius (variable declaration) 
float fahr; // fahrenheit (variable declaration)
printf("Enter a value for the temperature in Celsius:");
scanf("%f", &cels );
fahr = (convertor * cels) + 32; // formula
printf("Fahrenheit temperature =%.1f \n" , fahr);
return 0;
}
