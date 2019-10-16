#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>\

/* This function takes the inputs of right endpoints, left endpoints, and the number of rectangles. It outputs the approximate area under the function 
   by left-end points, right-end points, and midpoint methods. 
*/

// setting up function to validate inputs
bool validateInput(double left, double right, int n) {
		if (left>=-10 && right<=10 && left<right && n>0)
			return true;
		else
			return false;
}

// setting up function to evaluate the function
double evalFunc(double x) {
	double y = 2*pow(x,2) - 7*x - 2;
	return y;
}

int main(void)
{
	double left = 0, right = 0, stepSize = 0, midPointEvaluation = 0, leftPointEvaluation = 0, rightPointEvaluation = 0, sumLeftPoints = 0, sumRightPoints = 0, sumMidPoints = 0;
	int numberRectangles = 0, n=0; 
	//double x = 0;
	
	printf("Enter the Left boundary: a, Right boundary: b, and No. of rectangles to use.\n");
	printf("To exit enter 0 0 0\n");
	scanf("%lf %lf %d", &left, &right, &numberRectangles);
	
// if user inputs '0 0 0', it terminates the program
	if (left == 0 && right == 0 && numberRectangles == 0) {
		printf("Invalid inputs...\n\n");
		printf("Terminating Main!\n");
		return 0;
	}
// validates user input. if the value of function validateInput is false, it repeats the code. 
	while (validateInput(left, right, numberRectangles) == false) {
		printf("Invalid inputs...\n");
		printf("Enter the Left boundary: a, Right boundary: b, and No. of rectangles to use.\n");
		printf("To exit enter 0 0 0\n");
		scanf("%lf %lf %d", &left, &right, &numberRectangles);
		if (left == 0 && right == 0 && numberRectangles == 0){
			printf("Invalid inputs...\n\n");
			printf("Terminating Main!\n");
			return 0;
		}
	}
// getting delta-x; increments for stepSize
	stepSize = (right - left)/numberRectangles;
	
	printf("With Step Size: %.4lf\n", stepSize);
	printf("The approximate integral of the f(x) = 2(x^2)-7x-2\n");
	printf("Bound between %.2lf and %.2lf, using %d rectangles is as follows\n\n", left, right, numberRectangles);
	
	n = numberRectangles;
	
	//Left-end point Calculation
	for (int i=1; i<=n; i++){
		leftPointEvaluation = evalFunc(left+(i-1)*stepSize)*stepSize;
		sumLeftPoints += leftPointEvaluation;
	}
	
	//Right-end point calculation
	for (int i=1; i<=n; i++){
		rightPointEvaluation = evalFunc(left+(i*stepSize))*stepSize;
		sumRightPoints += rightPointEvaluation;
	}
	
	//Midpoint calculation
	for (int i=1; i<=n; i++) {
		midPointEvaluation = evalFunc(left+(i-0.5)*stepSize)*stepSize;
		sumMidPoints += midPointEvaluation;
	}
	
	printf("Mid point evaluation approximate: %.4lf\n", sumMidPoints);
	printf("Left point evaluation approximate: %.4lf\n", sumLeftPoints);
	printf("Right point evaluation approximate: %.4lf\n", sumRightPoints);
	
	return 0;
}
