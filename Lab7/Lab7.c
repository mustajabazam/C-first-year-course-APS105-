#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void printBoard (char board[][26], int n);
//bool positionInBounds (int n, int row, int col);
//bool checkLegalInDirection (char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
//bool checkMove (char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);


int main(void) {
	int boardDimensions = 0; 
//	int row = 0;
//	int col = 0;
//	int deltaRow;
//	int deltaCol;
	char colour;
	char rowChar;
	char colChar;
	char board[boardDimensions][26];
	
	printf("Enter the board dimension: ");
	scanf("%d", &boardDimensions);
	
	printBoard(board, boardDimensions);
	
//	while (colour != '!' && row != 33 && col != 33) {
//		printf("Enter board configuration:\n");
//		scanf("%c%d%d", &colour, &row, &col);
//		row = row - 97;
//		col = col - 97;
//		board[row][col] = colour;
//	}

		//printf("Enter board configuration:\n");
		//scanf("%c%c%c", &colour, &rowChar, &colChar);
		//row = (int)rowChar - 97;
		//col = (int)colChar - 97;
		//board[row][col] = colour;
	
//	do {
//		printf("Enter board configuration:\n");
//		scanf("%c%c%c", &colour, &rowChar, &colChar);
//		row = (int)rowChar - 97;
//		col = (int)colChar - 97;
//		board[row][col] = colour;
//	} while (colour != '!' && row != 33 && col != 33);
	
	printBoard(board, boardDimensions);
//	
//	
//	printf("Available moves for W:");
//	
//	printf("Available moves for B:");
//	
//	printf("Enter a move:\n");
//	scanf("%c%d%d", &colour, &row, &col);
//	if (checkMove) {
//		board[row][col] = colour;
//	} else if (!checkMove) {
//		printf("Invalid move.");
//	}
	
	
}

void printBoard(char board[][26], int n) {
	int i, j;
	printf("  "); 
	for (i = 0; i < n; i++) {
		printf("%c", 'a' + i);
	}
	printf("\n");
	
	for (i=0; i<n; i++) {
		printf("%c ", 'a'+ i);
		for (j=0; j<n; j++) {
			if (i == (n / 2) - 1) {
				if (j == (n / 2) - 1) {
					board[i][j] = 'W';
				} else if (j == n / 2) {
					board[i][j] = 'B';
				} else {
					board[i][j] = 'U';
				}
			} else if (i == n / 2) {
				if (j == (n / 2) - 1) {
					board[i][j] = 'B';
				} else if (j == n / 2) {
					board[i][j] = 'W';
				} else {
					board[i][j] = 'U';
				}
			} else {
				board[i][j] = 'U';
			}
			
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
}
//
//bool positionInBounds (int n, int row, int col) {
//	if (row >= n || col >= n) {
//		return false;
//	} else {
//		return true;
//	}
//}
//
//bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
//	bool walkFurther = true;
//	char oppositeColour;
//	int counter = 2;
//	
//	
//	if (colour == 'B') {
//		oppositeColour = 'W';
//	} else if (colour == 'W') {
//		oppositeColour = 'B';
//	}
//	
//	if (board[row + deltaRow][col + deltaCol] == colour || (!positionInBounds(n, row + deltaRow, col + deltaCol))) {
//		return false;
//	} else {
//		while (walkFurther) {
//			if (board[row + counter*deltaRow][col + counter*deltaCol] == 'U' || board[row + counter*deltaRow][col + counter*deltaCol] == positionInBounds(n, row + (counter*deltaRow), col + (counter*deltaCol)) || board[row + counter*deltaRow][col + counter*deltaCol] == oppositeColour) {
//				return true;
//				walkFurther = false;
//			} else {
//				counter ++;
//			}
//		}
//	}
//}
//
//bool checkMove (char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
//	for (deltaRow = -1; deltaRow < 2; deltaRow++) {
//		for (deltaCol = -1; deltaCol < 2; deltaCol++) {
//			if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)) {
//				return true;
//			} else if (!checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)) {
//				return false;
//			}
//		}
//	}
//}
