#include <stdio.h> // access to standard input/output library 

int main(void)
{
    char character;
    printf("Enter a character: ");
    scanf("%c", &character);
    printf("%c%c\n\n",character,character);

    return 0;
}
