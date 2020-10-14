#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <sysinfoapi.h>

char displayValues[3] = {'_', 'X', 'O' };

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

int playerInput(int board[]) {
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

int computerInput(int board[]) {
	for (int i = 8; i > 0; i--) {
		if (board[i] == 0) {
			board[i] = 2;
			break;
		}
	}

	printf("\nComputer Move: \n");
}

int checkWin(int board[]) {
	if (board[0] & board[1] & board[2]) {
		return board[0];
	}
	else if (board[0] & board[4] & board[8]) {
		return board[0];
	}
	else if (board[0] & board[3] & board[6]) {
		return board[0];
	}
	else if (board[1] & board[4] & board[7]) {
		return board[1];
	}
	else if (board[2] & board[5] & board[8]) {
		return board[2];
	}
	else if (board[2] & board[4] & board[6]) {
		return board[2];
	}
	else if (board[3] & board[4] & board[5]) {
		return board[3];
	}
	else if (board[6] & board[7] & board[8]) {
		return board[6];
	}

	return 100;
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
		playerInput(board);

		//show updated board
		displayBoard(board);

		//check win
		if (checkWin(board) == 1) {
			printf("\n You Win!\n");
			break;
		}

		//calculate computer input
		computerInput(board);

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