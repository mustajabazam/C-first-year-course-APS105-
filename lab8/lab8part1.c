#include <stdio.h>
#include <stdbool.h>
#define BLACK 'B'
#define WHITE 'W'
#define UNOCCUPIED 'U'
#define INITIAL_POSITION 'a'
#define COMPUTER 'C'
#define HUMAN 'H'

// Converting between Alphabet Index and Number Index
int convertIndex (char alphabet) {
	int num = alphabet - INITIAL_POSITION;
	return num;
}

//Filling the Board
void printBoard(char board[][26], int n) {
	int i = 0, j = 0;
	printf ("  ");
	for (j = 0; j < n; j++) {
		printf ("%c", INITIAL_POSITION + j); // printing the row alphabets
	}
	printf ("\n");
	j = 0;
	for (i = 0; i < n; i++) {
		printf ("%c ", INITIAL_POSITION + i); //printing the column alphabets
		for (j = 0; j < n; j++) {
			printf ("%c", board[i][j]); // printing the rows of the board
		}
		printf ("\n"); // moving to the next row
	} 
}

// Setting Up an nxn Board
int boardSetUp (void) {
	int n;
	printf ("Enter the board dimension: ");
	scanf ("%d", &n);
	return n;
}

// Setting Up the Colour for Computer
char computerColourSetUp (void) {
	char computerColour;
	printf ("Computer plays (B/W): ");
	scanf (" %c", &computerColour);
	return computerColour;
}

// Setting Up the Colour for the Human
char humanColourSetUp (char computerColour) {
	if (computerColour == WHITE)
		return BLACK;
	else
		return WHITE;
}

// Switching Between Players
char currentPlayer (char computerColour) {
	if (computerColour == BLACK)
		return COMPUTER;
	else
		return HUMAN;
}

// Filling the nxn Portion of 26x26 Array
void boardFill (char board[][26], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = UNOCCUPIED; // filling the nxn portion of 26x26 array with "U"
		}
	}
	// Putting in the initial pieces
	board[n/2-1][n/2-1] = WHITE;
	board[n/2-1][n/2] = BLACK;
	board[n/2][n/2-1] = BLACK;
	board[n/2][n/2] = WHITE;
	
	printBoard (board, n);
}

// Testing if the Given Position Is Within the Bounds of the Board
bool positionInBounds(int n, char row, char col) {
	if ((row - INITIAL_POSITION >= 0) && (row - INITIAL_POSITION < n) && (col - INITIAL_POSITION >= 0) && (col - INITIAL_POSITION < n))
		return true;
	else
		return false;
}

// Testing if It Is Legal to Place a Piece at a Certain Point (in One Direction)
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol) {
	int rowNum = convertIndex(row);
	int colNum = convertIndex(col);
	if (board[rowNum][colNum] != UNOCCUPIED) // if the position the user is trying to put a piece on is already occupied
		return false;
	row += deltaRow; // "looking ahead" 1 row above/below
	col += deltaCol; // "looking ahead" 1 column to the left/right
	rowNum = convertIndex(row); // converting the row alphabet to number (a = 0)
	colNum = convertIndex(col); // converting the column alphabet to number (a = 0)
	bool boundsTest = positionInBounds(n, row, col); // testing if the position that the computer is "looking ahead" is within the bounds of the board
	if (!boundsTest) // if the position that the computer is "looking ahead" is outside the board
		return false;
		
	if ((colour == WHITE) && (board[rowNum][colNum] != BLACK)) // if there is a black piece in the direction that the computer is looking ahead (player = white)
		return false;
	if ((colour == BLACK) && (board[rowNum][colNum] != WHITE)) // if there is no white piece in the direction that the computer is looking ahead (player = black)
		return false;
		
	if ((colour == WHITE) && (board[rowNum][colNum] == BLACK) /* if there is no black piece in the direction that the computer is looking ahead (player = white) */) {
		while (boundsTest /* while the position that the computer is "looking ahead" is inside the board */) {
			if (board[rowNum][colNum] == WHITE) // if there is a white piece to "sandwich" the black piece with
				return true;
			if (board[rowNum][colNum] == UNOCCUPIED) // if there is an unoccupied space
				return false;
			// Further "looking ahead" in the direction given until there is a white piece to "sandwich" the black piece with (or finding an unoccupied place)
			row += deltaRow;
			col += deltaCol;
			rowNum = convertIndex(row);
			colNum = convertIndex(col);
			boundsTest = positionInBounds(n, row, col);
		}
		return false;
	}
	
	else { // if there is a white piece in the direction that the computer is looking ahead (player = black)
		while (boundsTest) {
			if (board[rowNum][colNum] == BLACK)
				return true;
			if (board[rowNum][colNum] == UNOCCUPIED)
				return false;
			row += deltaRow;
			col += deltaCol;
			rowNum = row - INITIAL_POSITION;
			colNum = col - INITIAL_POSITION;
			boundsTest = positionInBounds(n, row, col);
		}
		return false;
	}
}

// Storing the Score (in One Direction)
int scoreOneDirection (char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol) {
	int score = 0; // score = 0 initially
	int rowNum = convertIndex(row);
	int colNum = convertIndex(col);
	bool legalTest = checkLegalInDirection (board, n, row, col, colour, deltaRow, deltaCol);
	if (!legalTest)
		return score; // score = 0 if it is illegal to place the piece at that point
	// Looking ahead in the given direction
	rowNum += deltaRow;
	colNum += deltaCol;
	if ((colour == WHITE) && (board[rowNum][colNum] == BLACK)) {
		while (board[rowNum][colNum] == BLACK) {
			score++; // adding a score
			// Looking further ahead in the given direction to see if more pieces can be flipped
			rowNum += deltaRow;
			colNum += deltaCol;
		}
		return score;
	}
	
	if ((colour == BLACK) && (board[rowNum][colNum] == WHITE)) {
		while (board[rowNum][colNum] == WHITE) {
			score++; // adding a score
			rowNum += deltaRow;
			colNum += deltaCol;
		}
		return score;
	}
	return score;
}

// Storing the Score in All Directions
int scoreAllDirections (char board[][26], int n, char row, char col, char colour) {
	int scoreNorth = scoreOneDirection (board, n, row, col, colour, -1, 0); // score in the north direction
	int scoreSouth = scoreOneDirection (board, n, row, col, colour, 1, 0); // score in the south direction
	int scoreEast = scoreOneDirection (board, n, row, col, colour, 0, 1); // score in the east direction
	int scoreWest = scoreOneDirection (board, n, row, col, colour, 0, -1); // score in the west direction
	int scoreNorthEast = scoreOneDirection (board, n, row, col, colour, -1, 1); // score in the northeast direction
	int scoreNorthWest = scoreOneDirection (board, n, row, col, colour, -1, -1); // score in the northwest direction
	int scoreSouthEast = scoreOneDirection (board, n, row, col, colour, 1, 1); // score in the southeast direction
	int scoreSouthWest = scoreOneDirection (board, n, row, col, colour, 1, -1); // score in the southwest direction
	int totalScore = scoreNorth + scoreSouth + scoreEast + scoreWest + scoreNorthEast + scoreNorthWest + scoreSouthEast + scoreSouthWest;
	return totalScore;
}

// Storing all Scores in a Matrix and Returning the Maximum Score
int maximumScore (int scoreMatrix[][26], char board[][26], int n, char colour) {
	int rowNum, colNum;
	for (rowNum = 0; rowNum < n; rowNum++) {
		for (colNum = 0; colNum < n; colNum++) {
			char row = INITIAL_POSITION + rowNum;
			char col = INITIAL_POSITION + colNum;
			scoreMatrix[rowNum][colNum] = scoreAllDirections (board, n, row, col, colour); // storing the score for each index into a new matrix
		}
	}
	// Calculating the Maximum Score
	int maxScore = 0;
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (scoreMatrix[i][j] > maxScore)
				maxScore = scoreMatrix[i][j];
		}
	}
	return maxScore;
}

// Flipping Pieces in One Direction
int flipOneDirection (char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol) {
	bool legalTest = checkLegalInDirection (board, n, row, col, colour, deltaRow, deltaCol);
	if (!legalTest) {
		return 0;
	}
	// Looking ahead in the given direction
	int rowNum = convertIndex(row);
	int colNum = convertIndex(col);
	rowNum += deltaRow;
	colNum += deltaCol;
	if ((colour == WHITE) && (board[rowNum][colNum] == BLACK)) {
		while (board[rowNum][colNum] == BLACK) {
			board[rowNum][colNum] = WHITE; // flipping black pieces to white
			// Looking further ahead in the given direction to see if more pieces can be flipped
			rowNum += deltaRow;
			colNum += deltaCol;
		}
		return 0;
	}
	
	if ((colour == BLACK) && (board[rowNum][colNum] == WHITE)) {
		while (board[rowNum][colNum] == WHITE) {
			board[rowNum][colNum] = BLACK; // flipping white pieces to black
			rowNum += deltaRow;
			colNum += deltaCol;
		}
		return 0;
	}
	return 0;
}

// Flipping Pieces in All 8 Directions
void flipAllDirections (char board[][26], int n, char row, char col, char colour) {
	flipOneDirection (board, n, row, col, colour, -1, 0); // flip north
	flipOneDirection (board, n, row, col, colour, 1, 0); // flip south
	flipOneDirection (board, n, row, col, colour, 0, 1); // flip east
	flipOneDirection (board, n, row, col, colour, 0, -1); // flip west
	flipOneDirection (board, n, row, col, colour, -1, 1); // flip northeast
	flipOneDirection (board, n, row, col, colour, -1, -1); // flip northwest
	flipOneDirection (board, n, row, col, colour, 1, 1); // flip southeast
	flipOneDirection (board, n, row, col, colour, 1, -1); // flip southwest
}

// Executing One Computer Move
int computerMove (int scoreMatrix[][26], char board[][26], int n, char computerColour) {
	int maxScore = maximumScore (scoreMatrix, board, n, computerColour); // calculating the maximum score
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (scoreMatrix[i][j] == maxScore) {
				// finding the lowest index with the maximum score
				char computerRow = INITIAL_POSITION + i;
				char computerCol = INITIAL_POSITION + j;
				flipAllDirections(board, n, computerRow, computerCol, computerColour);
				board [i][j] = computerColour;
				printf ("Computer places %c at %c%c.\n", computerColour, computerRow, computerCol);
				printBoard(board, n);
				return 0;
			}
		}
	}
	return 0;
}

// Executing One Human Move
bool humanMove (int scoreMatrix[][26], char board[][26], int n, char humanColour) {
	char row, col;
	maximumScore(scoreMatrix, board, n, humanColour); // storing scores (to store index of invalid moves)
	printf ("Enter move for colour %c (RowCol): ", humanColour);
	scanf (" %c%c", &row, &col);
	int rowNum = convertIndex(row);
	int colNum = convertIndex(col);
	if (scoreMatrix[rowNum][colNum] != 0 /* if the move is valid */) {
		char humanRow = INITIAL_POSITION + rowNum;
		char humanCol = INITIAL_POSITION + colNum;
		flipAllDirections(board, n, humanRow, humanCol, humanColour);
		board[rowNum][colNum] = humanColour;
		printBoard(board, n);
		return true; // returns true if the move is valid
	}
	
	else {
		printf ("Invalid move.\n");
		return false; // returns false if the move is invalid
	}

}

// Checking for Winner
int checkWinner (char board[][26], int n) {
	int blackCount = 0, whiteCount = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == BLACK) {
				blackCount++;
			}
			else if (board[i][j] == WHITE) {
				whiteCount++;
			}
		}
	}
	
	if (blackCount == whiteCount) {
		printf ("Draw!\n");
		return 0;
	}
	
	if (blackCount > whiteCount) {
		printf ("B Player Wins.\n");
		return 0;
	}
	
	else {
		printf ("W player Wins.\n");
		return 0;
	}
}

// Checking if the Board is Full
bool checkFullBoard (char board[][26], int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (board[i][j] == UNOCCUPIED)
				return false;
		}
	}
	return true;
}

int main (void) {
	// Setting Up the Board
	int dimension = boardSetUp();
	char board[26][26];
	char computer = computerColourSetUp();
	char human = humanColourSetUp (computer);
 	boardFill (board, dimension);
	int scoreMatrix[26][26];
	int noMoveCount = 0; // counting the number of times when the player cannot make a valid move
	bool validMove = true; 
	bool checkFull = false;
	char player = currentPlayer(computer);
		
	do {
		// Computer Move
		if (player == COMPUTER) {
			int maxScore = maximumScore(scoreMatrix, board, dimension, computer);
			checkFull = checkFullBoard(board, dimension);
			if (maxScore == 0) {
				if ((noMoveCount == 0 || noMoveCount == 1) && !checkFull) {
					printf ("%c player has no valid move.\n", computer);
					player = HUMAN;
					noMoveCount++;
				}
			}
			else if (maxScore != 0) {
				computerMove (scoreMatrix, board, dimension, computer);
				player = HUMAN;
				noMoveCount = 0;
			}
		}
		
		// Human Move
		if (player == HUMAN) {
			int maxScore = maximumScore(scoreMatrix, board, dimension, human);
			checkFull = checkFullBoard(board, dimension);
			if (maxScore == 0) {
				if ((noMoveCount == 0 || noMoveCount == 1) && !checkFull) {
					printf ("%c player has no valid move.\n", human);
					player = COMPUTER;
					noMoveCount++;
				}
			}
			
			else if (maxScore != 0) {
				validMove = humanMove(scoreMatrix, board, dimension, human);
				player = COMPUTER;
				noMoveCount = 0;
			}
			
		}
	} while (noMoveCount < 2 && validMove && !checkFull); // while at least one player has a valid move & the human move is valid & the board is not full
	
	checkWinner(board, dimension); // checking for winner
	return 0;
}