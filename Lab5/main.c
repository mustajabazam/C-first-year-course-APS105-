#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

void input(int *num); //prototyping functions
int add4(int num);
int shift(int num);
void printOutput(int encryptNum, int originalNum);

int main(void) {
	int inputNumber=0;
	
	input(&inputNumber);
	
	int add4Num = add4(inputNumber);
	int shiftedNumber = shift(add4Num);
	printOutput(shiftedNumber, inputNumber);
}

void input(int* num) {
	printf("Please enter an integer greater than 99999: ");
	scanf("%d", num);
	while (*num<=99999){
		printf("Incorrect input.\n");
		printf("Please enter an integer greater than 99999: ");
		scanf("%d", num);
	}
	printf("The number entered is %d\n", *num);
}

int add4(int num) {
	int newNumber = 0;
	int multiplier = 1;
	while (num > 0) {
		int moduloNum;
		moduloNum = num % 10;
		num /= 10;
		
		moduloNum += 4;
		if (moduloNum >= 10) {
			moduloNum -= 10;
		}
		
		newNumber += (moduloNum * multiplier);
		multiplier *= 10;
	}
	return newNumber;
}

int shift(int num) {
	int moduloNum, encryptedNumber;
	int copyOfNum = num;
	int multiplier = 1;
	
	while (copyOfNum > 0) {
		moduloNum = copyOfNum%10;
		copyOfNum /= 10;
		multiplier *= 10;
	}
	
	encryptedNumber = num - (moduloNum*(multiplier/10));
	encryptedNumber *= 10;
	encryptedNumber += moduloNum;
	
	return encryptedNumber;
}

void printOutput(int encryptNum, int originalNum){
	printf("Original number: %d\n", originalNum);
	printf("Encrypted number: %d\n", encryptNum);
}
