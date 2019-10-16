#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* This program takes the price of a coffee, the user's monthly budget, and the how many purchases provides a free coffee. 
 * It outputs how many coffees the user can buy, how many free coffees they can get with the monthly budget, the average coffee price, and the leftover money and coupons.
 */

int main(void)
{
	double costCoffee = 0, monthlyBudget = 0, leftoverMoney = 0, averageCoffeePrice = 0; 
	int freeCoffeeCoupon = 0, coffeePurchases = 0, numberOfFreeCoffees = 0, leftoverCoupons = 0; 
	
	
	printf("How much does a coffee cost?\n");
	scanf("%lf", &costCoffee); //accepting and assigning input from user
	if (costCoffee <= 0) {
		printf("Invalid Input.\n");
		return 0; //if the cost of a coffee is less than $0.01, then program exits
	}
	
	printf("How many coupons does it take to get a free coffee?\n");
	scanf("%d", &freeCoffeeCoupon);
	if (freeCoffeeCoupon < 1) {
		printf("Invalid Input.\n");
		return 0; //if the number of coupons to get a free coffee is less than 1, then program exits
	}
	
	printf("How much money do you have to spend on coffee this month?\n");
	scanf("%lf", &monthlyBudget);
	if (monthlyBudget < 0) {
		printf("Invalid Input.\n");
		return 0; //if the monthly budget for user is negative, then program exits
	}
	
	// Calculations with variables
	coffeePurchases = monthlyBudget/costCoffee;
	numberOfFreeCoffees = coffeePurchases/freeCoffeeCoupon;
	leftoverCoupons = (coffeePurchases+numberOfFreeCoffees) - (freeCoffeeCoupon*numberOfFreeCoffees);
	leftoverMoney = monthlyBudget - (costCoffee*coffeePurchases);
	
	averageCoffeePrice = (costCoffee*coffeePurchases)/(coffeePurchases+numberOfFreeCoffees);
	
	printf("This month, you can purchase %d coffees at %.2lf.\n", coffeePurchases, costCoffee);
	
	//Below, if the number of coffees purchased is less than the number of coupons required for a free coffee,the program will print differently 
	if (coffeePurchases >= freeCoffeeCoupon) {
		printf("You will be able to redeem an additional %d coffee(s) from coupons.\n", numberOfFreeCoffees);
	} else {
		printf("You will not be able to redeem any additional coffees from coupons this month.\n"); 
	}
	
	printf("At the end of the month, you will have $%.2lf and %d coupon(s) remaining.\n", leftoverMoney, leftoverCoupons);
	printf("On average, you spent $%.2lf on each cup of coffee this month.\n", averageCoffeePrice);
	
	return 0;
}
