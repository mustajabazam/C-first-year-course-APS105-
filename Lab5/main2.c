#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

int rollDice(void);
bool playGame(void);
void winLoss(void);

int main(void) {
	winLoss();
}

int rollDice(void) {
	int firstDice, secondDice, sumOfRoll;
	
	firstDice = rand() % 6 + 1;
	secondDice = rand() % 6 + 1;
	sumOfRoll = firstDice + secondDice;
	
	return sumOfRoll;
}

bool playGame(void) {
	int roll = rollDice();
	printf("You rolled: %d\n", roll);
	if (roll == 7 || roll == 11) {
		printf("You win!\n");
		return true;
	} else if (roll == 2 || roll == 3 || roll == 12) {
		printf("You lose!\n");
		return false;
	} else {
		printf("Your point is: %d\n", roll);
		int newRoll;
		do {
			newRoll = rollDice();
			printf("You rolled: %d\n", newRoll);
		} while (newRoll != 7 && newRoll != roll);
		
		if (newRoll == roll) {
			printf("You win!\n");
			return true;
		} else {
			printf("You lose!\n");
			return false;
		}
	}
}

void winLoss(void) {
	int wins = 0, losses = 0;
	char playAgain;
	bool result;
	
	do {
		result = playGame();
		if (result) {
			wins ++;
		} else {
			losses ++;
		}
		printf("Play again? ");
		scanf(" %c", &playAgain);
	} while(playAgain == 'y' || playAgain == 'Y');
	printf("\n\nWins: %d\n", wins);
	printf("Losses: %d\n", losses);
}
