
#include <stdio.h>

int num;
int main(){


printf("\n Enter a positive integer:");  
scanf("%d", &num);
do {
    printf("%d ", num % 10); 
    num /= 10;
} while (num > 0);

printf("\n");
return 0;
}