#include <stdio.h>
#include <stdlib.h>

struct Board {
	char** data;
	int rows;
	int cols;
};
typedef struct Board Board;

Board readBoardFromStdIn() {
	Board board;

	scanf("%d %d", &board.rows, &board.cols);
	getchar(); //read the newline following the two integers

	board.data = malloc((sizeof(char*)) * board.rows);

	for (int i = 0; i < board.rows; i++) {
		board.data[i] = malloc(sizeof(char) * board.cols + 1);
		for (int j = 0; j < board.cols; j++) {
			board.data[i][j] = getchar();
		}
		getchar(); //read the newline following the row
		board.data[i][board.cols] = '\0';
	}

	return board;
}

void printBoard(Board board) {
	for (int i = 0; i < board.rows; i++) {
		printf("%s\n", board.data[i]);
	}
}

void debugBoard(Board board) {
	printf("%d %d\n", board.rows, board.cols);
	for (int i = 0; i <  board.rows; i++) {
		for (int j = 0; j <  board.cols + 1; j++) {
			printf("%u\n", (unsigned char)board.data[i][j]);
		}
	}

	printBoard(board);
}

int main() {
	char EMPTY = ' ';
	char ALIVE = '+';
	char DEAD = '*';

	int steps;

	Board board = readBoardFromStdIn();
	debugBoard(board);
}