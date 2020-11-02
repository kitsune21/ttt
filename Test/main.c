#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char displayValues[3] = {'_', 'X', 'O' };

int possibleWinCombos[8][3] = { {0, 1, 2}, {0, 4, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {2, 4, 6}, {3, 4, 5}, {6, 7, 8} };
int corners[4] = { 0, 2, 6, 8 };

void displayBoard(int board[]) {
	printf("\nCurrent Board:\n\n");
	for (int i = 0; i < 9; i++) {
		if ((i + 1) % 3 == 0) {
			printf("%c \n", displayValues[board[i]]);
		}
		else {
			printf("%c | ", displayValues[board[i]]);
		}
	}
}

void playerInput(int board[]) {
	int square;
	printf("\nPick a square: ");
	scanf_s("%d", &square);
	square--;
	
	while (square > 9 || board[square] != 0) {
		printf("\nPlease pick a different square: ");
		scanf_s("%d", &square);
		square--;
	}

	if (displayValues[board[square]] == '_') {
		board[square] = 1;
	}
}

void computerInput(int board[]) {
	int moveMade = 0;

	if (board[4] == 0) {
		board[4] = 2;
	}
	else {
		for (int i = 0; i < 8; ++i) {
			//Find dangerous position
			if (checkSquares(possibleWinCombos[i], board) >= 1) {
				//find the empty square
				for (int j = 0; j < 3; ++j) {
					if (board[possibleWinCombos[i][j]] == 0 && !moveMade) {
						if(board[possibleWinCombos[i][j]] == 0){
							board[possibleWinCombos[i][j]] = 2;
							moveMade = 1;
							break;
						}
					}
				}
			}
		}
		//Prioritize corners if no danger
		if (!moveMade) {
			for (int i = 0; i < 9; ++i) {
				if (board[corners[i]] == 0) {
					board[corners[i]] = 2;
					moveMade = 1;
					break;
				}
			}
		}
		//fill in anything else if nothing else to do
		if (!moveMade) {
			for (int i = 0; i < 9; ++i) {
				if (board[i] == 0) {
					board[i] = 2;
					moveMade = 1;
				}
			}
		}
		if (!moveMade) {
			printf("No move made\n");
		}
	}

	printf("\nComputer Move: \n");
}

int checkSquares(int possibleWin[], int board[]) {
	int count = 0;

	if (board[possibleWin[0]] & board[possibleWin[1]]) {
		count++;
	}
	if (board[possibleWin[1]] & board[possibleWin[2]]) {
		count++;
	}
	if (board[possibleWin[0]] & board[possibleWin[2]]) {
		count++;
	}

	return count;
}

int checkWin(int board[]) {
	for (int i = 0; i < 8; ++i) {
		if (checkSquares(possibleWinCombos[i], board) == 3) {
			return board[possibleWinCombos[i][0]];
		}
	}

	return 100;
}

int checkTie(int board[]) {
	for (int i = 0; i < 9; ++i) {
		if (board[i] == 0) {
			return 0;
		}
	}

	return 1;
}

int main() {
	long first;
	int board[9];

	//instructions
	printf("Welcome to Tic-Tac-Toe!\nTo play you will input the corresponding square space on your turn. Here is the board: \n");
	printf("1|2|3\n4|5|6\n7|8|9\n");

	//determine comp/human first
	first = time(NULL) % 2;
	printf("Player %ld will go first.\n", first + 1);

	//makes sure the board is all 0
	for (int i = 0; i < 9; i++) {
		board[i] = 0;
	}

	if (first) {
		computerInput(board);
		displayBoard(board);
	}

	//start game loop
	while (1) {
		//ask for input
		if (!checkTie(board)) {
			playerInput(board);
		} else {
			printf("Cat's Game\n");
			break;
		}

		//show updated board
		displayBoard(board);

		//check win
		if (checkWin(board) == 1) {
			printf("\n You Win!\n");
			break;
		}

		//calculate computer input
		if (!checkTie(board)) {
			computerInput(board);
		} else {
			printf("Cat's Game\n");
			break;
		}

		//show updated board
		displayBoard(board);

		//check win
		if (checkWin(board) == 2) {
			printf("\nYou Lose!\n");
			break;
		}
	}
	
	return 0;
} 