   #include <stdio.h>		/* give access to the stdio.h library */
         int main(void)
	{
		printf("%d\n", +455);           
		printf("%d\n\n\n", -455);
		
		printf("%e\n", 1234567.89);
		printf("%f\n\n\n", 1234567.89);

		printf("%c\n", 'A');
		printf("%s\n\n\n", "This is a string");

		printf("%4d\n" , 1);
		printf("%4d\n" , 12);
		printf("%4d\n\n\n" , 123);

        	printf("%4d\n" , -1);
		printf("%4d\n" , -12);
		printf("%4d\n\n\n" , -123);


	        printf(" %.4d\n%.9d\n" , 873, 873);
     
     		printf(" %.3f\n%.6f\n\n\n\n ", 123.94536, 123.94536);
      
    		printf("%10s%10d%10c%10f\n\n" , "hello", 7, 'a' , 1.23);
        	printf("%-10s%-10d%-10c%-10f\n\n\n" , "hello",7, 'a' , 1.23);


	        printf("%d\n\t%d\n" , 786, -786);
        	printf("%+d\n\t%+d\n" , 786, -786);

}
