#include <stdio.h> // access to standard input/output library 


int main(void)
{
    int a = 9;

    a = -a;
    printf("a = %+d\n",a);

    a -= a;
    printf("a = %+d\n",a);

    --a;
    printf("a = %+d \n",a);

    a = (a == a);
    printf("a = %+d \n",a);

    return 0;
}


