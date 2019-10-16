#include <stdio.h>
#include <math.h>

/*  This program begins by declaring and initializing the varirables which will be used. 
	It outputs messages to the user using the 'printf' function, and detects user input using the 'scanf' function
	Embedded, the program converts the annual interest rate to a monthly interest rate 
	Lastly, it calculates the monthly payments and total cost of the purchase
*/

int main(void) {
	//defining and initializing variables
	double priceOfItem = 0, annualInterestRate = 0, monthlyInterestRate = 0, monthlyPayment = 0, costPurchase = 0; int repaymentPeriod = 0;
	
	printf("Enter the purchase price of the item: ");
	scanf("%lf", &priceOfItem); //detecting and storing input from user
	printf("Enter the interest rate per year as a percentage: ");
	scanf("%lf", &annualInterestRate); //detecting and storing input from user
	
	monthlyInterestRate = annualInterestRate/12; //converting annual interest rate to monthly interest rate
	
	printf("Enter the number of months for repayment: ");
	scanf("%d", &repaymentPeriod); //detecting and storing input from user
	
	//inputting values of variables into the equation
	monthlyPayment = (monthlyInterestRate/100.0)/(1 - pow((1+(monthlyInterestRate/100.0)),(-1*repaymentPeriod))) * priceOfItem;
	costPurchase = monthlyPayment*repaymentPeriod; //calculating the total cost of purchase
	
	printf("The monthly payment is: %.2lf \n", monthlyPayment);
	printf("The total cost of the purchase is: %.2lf \n", costPurchase); //printing and displaying required outputs
	
	return 0;
}
