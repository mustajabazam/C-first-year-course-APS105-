#include <stdio.h>
#include <math.h>

int main(void) {

		double number1=0, number2=0, product=0, difference=0, sumSquareRoot=0;
		
		printf("Enter two positive numbers:  ");
		scanf("%lf %lf", &number1, &number2);
		
		product = number1 * number2;
		difference = number1 - number2;
		sumSquareRoot = sqrt(number1) + sqrt(number2);
		
		printf("The product is: %.2lf, the difference is: %.2lf and the sum of roots is: %.2lf \n", product, difference, sumSquareRoot);
		
	return 0;
}