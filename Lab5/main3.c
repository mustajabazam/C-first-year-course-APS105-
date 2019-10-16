#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void inputDate(int *day, int *month, int *year);
void calculateDay(int day, int month, int year);

int main(void) {
	int day, month, year;
	
	inputDate(&day, &month, &year);
	calculateDay(day, month, year);
	
//	int *dayPtr = &day;
//	int *monthPtr = &month;
//	int *yearPtr = &year;
//	
//	inputDate(dayPtr, monthPtr, yearPtr)
}

void inputDate (int *day, int *month, int *year) {
	printf("Please enter a date: ");
	scanf("%d/%d/%d", day, month, year);
}

void calculateDay(int day, int month, int year) {
	int a, b, c, d, w, x, y, z, r;
	const char* weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	
	if (month > 2) {
		a = month - 2;
	} else {
		a = month + 10;
	}
	
	b = day;
	
	c = year % 100;
	if (month <= 2 && c != 0) {
		c--;
	} else if (month <= 2 && c == 0) {
		c = 99;
	}
	
	d = year / 100;
	if (month <= 2 && c == 99) {
		d--;
	}
	
	w = (13 * a - 1) / 5;
	x = c / 4;
	y = d / 4;
	z = w + x + y + b + c - 2 * d;
	r = z % 7;
	if (r < 0) {
		r += 7;
	}
	
	printf("The day %d/%d/%d is a %s.\n", day, month, year, weekdays[r]);
}