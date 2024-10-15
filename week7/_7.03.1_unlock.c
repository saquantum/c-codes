#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

#define ROWS 3
#define COLUMNS 3
#define EMPTY 0

void paths(int x0, int y0, int count, int board[ROWS][COLUMNS], int* total);
bool hasnext(int x, int y, int board[ROWS][COLUMNS]);
bool isinboard(int x, int y);
void clearboard(int board[ROWS][COLUMNS]);
int printpath(int board[ROWS][COLUMNS], int mode);
void test();

int main() {

	test();
	int total=0;
	int board[ROWS][COLUMNS];
	clearboard(board);
	paths(0,0,1,board,&total);
	printf("total paths=%d\n", total);

}

void paths(int x0, int y0, int count, int board[ROWS][COLUMNS], int* total) {
	board[y0][x0] = count;
	if (!hasnext(x0, y0, board)) {
		if (printpath(board,0)) {
			(*total)++;
		}
		board[y0][x0] = EMPTY;
		return;
	}
	char directions[] = {'u','r','d','l'};
	for (int i = 0; i < 4; i++) {
		int x = x0;
		int y = y0;
		char c = directions[i];
		x = (c == 'r') ? x + 1 : (c == 'l') ? x - 1 : x;
		y = (c == 'u') ? y - 1 : (c == 'd') ? y + 1 : y;
		if (isinboard(x, y) && board[y][x]==EMPTY) {
			paths(x, y, count + 1, board, total);
		}
	}
	board[y0][x0] = EMPTY;
}

bool hasnext(int x, int y, int board[ROWS][COLUMNS]) { // return 'u' 'r' 'd' 'l'. if no next possible move, return 0.
	return (isinboard(x - 1, y) && board[y][x - 1] == EMPTY) ||
		(isinboard(x, y + 1) && board[y + 1][x] == EMPTY) ||
		(isinboard(x + 1, y) && board[y][x + 1] == EMPTY) ||
		(isinboard(x, y - 1) && board[y - 1][x] == EMPTY);
}

bool isinboard(int x, int y) {
	return 0 <= x && x < COLUMNS && 0 <= y && y < ROWS;
}

int printpath(int board[ROWS][COLUMNS], int mode) {
	// mode=0: print
	// mode=1: no printing
	int* a = (int*)calloc(ROWS * COLUMNS,sizeof(int));
	if (!a) {
		printf("not enough heap memory.\n");
		free(a);
		return -1;
	}
	for (int j = 0; j < ROWS; j++) {
		for (int i = 0; i < COLUMNS; i++) {
			int k = j + i * COLUMNS + 1;
			if (board[j][i] != EMPTY) {
				a[board[j][i] - 1] = k;
			}
		}
	}
	if (!mode) {
		printf("[ ");
	}
	int count = 0;
	for (int k = 0; k < ROWS * COLUMNS;k++) {
		if (a[k]) { 
			if (!mode) {
				printf("%d", a[k]);
			}
			count++;
		}
		if (k + 1 < ROWS * COLUMNS && a[k + 1]) {
			if (!mode) {
				printf("->");
			}
		}
	}
	if (!mode) {
		printf(" ], length = %d\n", count);
	}
	free(a);
	return count;
}

void clearboard(int board[ROWS][COLUMNS]) {
	for (int j = 0; j < ROWS; j++) {
		for (int i = 0; i < COLUMNS; i++) {
			board[j][i] = EMPTY;
		}
	}
}

void test() {
	int board[ROWS][COLUMNS];
	clearboard(board);
	assert(hasnext(0, 0, board));
	assert(hasnext(ROWS - 1, 0, board));
	assert(hasnext(0, COLUMNS - 1, board));
	assert(hasnext(ROWS - 1, COLUMNS - 1, board));
}
