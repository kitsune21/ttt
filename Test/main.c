#include <stdio.h>
#include <stdlib.h>

int square;
int board[9];


int randInRange(int min, int max)
{
	return min + (int)(rand() / (double)(RAND_MAX + 1) * (max - min + 1));
}

char returnChar(int value) {
	if (value == 1) {
		return 'X';
	}
	else if (value == 2) {
		return 'O';
	}
	else {
		return '_';
	}
}

void displayBoard(int board[]) {
	printf("\nCurrent Board:\n\n");
	for (int i = 0; i < 3; i++) {
		if (i < 2) {
			printf("%c | ", returnChar(board[i]));
		}
		else {
			printf("%c \n", returnChar(board[i]));
		}
	}
	for (int i = 3; i < 6; i++) {
		if (i < 5) {
			printf("%c | ", returnChar(board[i]));
		}
		else {
			printf("%c \n", returnChar(board[i]));
		}
	}
	for (int i = 6; i < 9; i++) {
		if (i < 8) {
			printf("%c | ", returnChar(board[i]));
		}
		else {
			printf("%c \n", returnChar(board[i]));
		}
	}
}

int playerInput() {
	printf("\nPick a square: ");
	scanf_s("%d", &square);
	square--;
	
	while (square > 9 || board[square] != 0) {
		printf("\nPlease pick a different square: ");
		scanf_s("%d", &square);
		square--;
	}

	if (returnChar(board[square]) == '_') {
		board[square] = 1;
	}
}

int computerInput() {
	for (int i = 8; i > 0; i--) {
		if (board[i] == 0) {
			board[i] = 2;
			break;
		}
	}

	printf("\nComputer Move: \n");
}

int checkWin() {
	for (int i = 1; i < 3; i++) {
		if (board[0] == i && board[1] == i && board[2] == i) {
			return i;
		}
		else if (board[0] == i && board[4] == i && board[8] == i) {
			return i;
		}
		else if (board[0] == i && board[3] == i && board[6] == i) {
			return i;
		}
		else if (board[1] == i && board[4] == i && board[7] == i) {
			return i;
		}
		else if (board[2] == i && board[5] == i && board[8] == i) {
			return i;
		}
		else if (board[2] == i && board[4] == i && board[6] == i) {
			return i;
		}
		else if (board[3] == i && board[4] == i && board[5] == i) {
			return i;
		}
		else if (board[6] == i && board[7] == i && board[8] == i) {
			return i;
		}
	}

	return 100;
}

int main() {
	int won = 0;
	int first;
	

	//instructions
	printf("Welcome to Tic-Tac-Toe!\nTo play you will input the corresponding square space on your turn. Here is the board: \n");
	printf("1|2|3\n4|5|6\n7|8|9\n");

	//determine comp/human first
	first = randInRange(0, 1);
	printf("Player %d will go first.\n", first + 1);

	for (int i = 0; i < 9; i++) {
		board[i] = 0;
	}

	//start game loop
	while (won == 0) {
		//ask for input
		playerInput();

		//show updated board
		displayBoard(board);

		//check win
		int testWin = checkWin();
		if (testWin == 1) {
			printf("\n You Win!\n");
			break;
		}


		//calculate computer input
		computerInput();

		//show updated board
		displayBoard(board);

		//check win
		testWin = checkWin();
		if (testWin == 2) {
			printf("\nYou Lose!\n");
			break;
		}
	}
	
	return 0;
} 