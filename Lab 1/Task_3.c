#include <stdio.h> // access to standard input/output library 
#define  convertor (5.0/9.0) // definition of a constant 
int main(void)
{
float cels; // celsius (variable declaration) 
float fahr; // fahrenheit (variable declaration)
printf("Enter a value for the temperature in Fahrenheit:");
scanf("%f", &fahr );
cels = convertor * (fahr - 32); // formula
printf("Celsius temperature =%.1f \n" , cels);
return 0;
}