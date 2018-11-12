#include <stdio.h>
#include <stdlib.h>


#define EMPTY ' '
#define ALIVE '+'
#define DEAD '*'

struct Board {
	char** data;
	int rows;
	int cols;
};
typedef struct Board Board;

/*
Board.data must be freed by caller.
*/
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

/*
Board.data must be freed by caller.
*/
Board copyBoard(Board board) {
	Board clone;


	clone.rows = board.rows;
	clone.cols = board.cols;
	clone.data = malloc((sizeof(char*)) * board.rows);

	for (int i = 0; i < board.rows; i++) {
		clone.data[i] = malloc(sizeof(char) * board.cols + 1);
		for (int j = 0; j < board.cols; j++) {
			clone.data[i][j] = board.data[i][j];
		}
		clone.data[i][board.cols] = '\0';
	}

	return clone;
}



int directions[3] = { -1, 0, 1 };
int neighbours(Board board, int row, int col) {
	int count = 0;
	
	// instead of enumerating all the directions by hard coding them,
	// we enumerate by looking at all of the combinations of 
	// -1, 0, 1 cross producted with -1, 0, 1 to produce:
	// (-1,-1), (-1, 0), (-1, 1),
	// ( 0,-1), ( 0, 0), ( 0, 1),
	// ( 1,-1), ( 1, 0), ( 1, 1)
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (directions[i] != 0 && directions[j] != 0 // (0, 0) just looks at yourself, which is not a neighbour
				&& row + directions[i] >= 0 && row + directions[i] < board.rows // make sure the row direction doesn't go out of bounds
				&& col + directions[j] >= 0 && col + directions[j] < board.cols // make sure the col direction doesn't go out of bounds
				&& board.data[row + directions[i]][col + directions[j]] == ALIVE // does the cell contain someone alive?
				) {
				count++;
			}
		}
	}
	
	return count;
}


void iterate(Board currentStep, Board nextStep) {

}

#define STEPS 100
int main() {
	int steps = STEPS;

	Board currentStep = readBoardFromStdIn();
	Board nextStep = copyBoard(currentStep);

	printBoard(currentStep);
	for (int i = 0; i < steps; i++) {
		iterate(currentStep, nextStep);
		printf("=================\n");
		printBoard(nextStep);
		Board swap = currentStep;
		currentStep = nextStep;
		nextStep = swap;
	}

}