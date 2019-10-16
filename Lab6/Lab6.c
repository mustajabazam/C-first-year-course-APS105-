#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>



void printBoard(int board[], int playerA, int playerB);
int requestValidInput(int board[], int playerA, int playerB);
int checkForWinner(int board[], int playerA, int playerB);
bool checkForStalemate(int board[], int playerA, int playerB);

/* 
  This program takes the inputs of position on a 1-D array and replaces them with letters 'A' or 'B' depending on the player. 
  This program plays the game tic-tac-to
 */

// this function prints the board's current state. Where there is an 11 or 22 for playerA or playerB, it prints A or B instead of that number
void printBoard(int board[], int playerA, int playerB) {
	for (int i = 0; i < 9; i++) {
		printf(" ");

		if (i % 3 == 0) {
			printf("\n");
		}
		if (board[i] == 11) {
			printf("A");
		} else if (board[i] == 22) {
			printf("B");
		} else {
			printf("%d", board[i]);
		}
	}
	printf("\n");
}

/* This function requests and validates the user's input of position. It prints different statements if the input position is already 
   taken, or if the input is not within the board's parameters. 
   This funtion returns the index value of the board input. 
*/
int requestValidInput(int board[], int playerA, int playerB) {
	int boardInput;
	bool flag = false;
	do {
		scanf("%d", &boardInput);
		if (boardInput > 0 && boardInput < 10) {
			if (board[boardInput - 1] != 11 && board[boardInput - 1] != 22) {
				flag = true;
			} else {
				printf("That position has been played, please try again.\n");
			}
		} else {
			printf("Invalid input, please try again.\n");
		}
	} while (!flag);
	
	return boardInput - 1;
}

//This function checks for stalemate in the board. If any value on the board is not 11 or 22, then returns false. 
//If every value is 11 or 22, return true
bool checkForStalemate(int board[], int playerA, int playerB) {
	for (int i = 0; i < 9; i++) {
		if (board[i] != 11 || board[i] != 22) {
			return false;
		}
	}
	
	return true;
}

//checks for all the different combinations to see if theres a winner, and returns the int value for which player won
int checkForWinner(int board[], int playerA, int playerB) {
	if ((board[0] == playerA && board[1] == playerA && board[2] == playerA) || (board[3] == playerA && board[4] == playerA && board[5] == playerA) || 
	    (board[6] == playerA && board[7] == playerA && board[8] == playerA) || (board[1] == playerA && board[4] == playerA && board[7] == playerA) || 
	    (board[2] == playerA && board[5] == playerA && board[8] == playerA) || (board[3] == playerA && board[6] == playerA && board[9] == playerA) ||
	    (board[1] == playerA && board[5] == playerA && board[9] == playerA) || (board[3] == playerA && board[5] == playerA && board[9] == playerA)) {
			return playerA;
		} else if ((board[0] == 22 && board[1] == 22 && board[2] == 22) || (board[3] == 22 && board[4] == 22 && board[5] == 22) || 
	    (board[6] == playerB && board[7] == playerB && board[8] == playerB) || (board[1] == playerB && board[4] == playerB && board[7] == playerB) || 
	    (board[2] == playerB && board[5] == playerB && board[8] == playerB) || (board[3] == playerB && board[6] == playerB && board[9] == playerB) ||
	    (board[1] == playerB && board[5] == playerB && board[9] == playerB) || (board[3] == playerB && board[5] == playerB && board[9] == playerB)) {
			return playerB;
		} 
		return 0;
}


int main(void) {
	
	//initialize board
	printf("\n");
	int playerA = 11, playerB = 22; 
	int boardInput, winner;
	bool gameOver;
	
	
	int board[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 
	
	
	int currentPlayer = playerA;
	gameOver = false;
	
	while (!gameOver) {
		
		printf("The current state of the Tic-tac-to Board:\n");
		printBoard(board, playerA, playerB);
		printf("\n");
		
		if (currentPlayer == playerA) { 
			printf("It is Player A's turn.\n");
		} else {
			printf("It is Player B's turn.\n");
		}
		
		
		printf("Please enter a valid position to play.\n"); 
		boardInput = requestValidInput(board, playerA, playerB);
		
		// update the game board
		board[boardInput] = currentPlayer;
		
		//switching player
		 if (currentPlayer == playerA) {
			 currentPlayer = playerB;
		 } else {
			 currentPlayer = playerA;
		 }
		
		winner = checkForWinner(board, playerA, playerB);
		
		if (winner == playerA || winner == playerB) {
			gameOver = true;
		} else if (checkForStalemate(board, playerA, playerB)) {
			gameOver = true;
		}
	}
	
	if (winner == playerA) {
		printf("Player A wins!\n");
	} else if (winner == playerB) {
		printf("Player B wins!\n");
	} else {
		printf("It's a draw!\n");
	}
	
	printBoard(board, playerA, playerB);
	
	return 0;
}


