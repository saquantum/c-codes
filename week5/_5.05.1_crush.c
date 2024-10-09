#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define ROWS 20
#define COLUMNS 5
#define PLAYINGHEIGHT 6

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

void solve(char board[ROWS][COLUMNS]);
bool falldown(char board[ROWS][COLUMNS]);
bool shiftarray(int shift, char arr[], int length, int pointer_dist);
bool three_in_a_sequence(int x, int y, char board[ROWS][COLUMNS]);
void random_initialize(char board[ROWS][COLUMNS], int colours);
void printboard(char board[ROWS][COLUMNS], int mode);
bool is_in_play_area(int x, int y);
bool is_in_board(int x, int y);
void test();

int main() {

	test();

	srand(5);
	char board[ROWS][COLUMNS] = { 0 };
	random_initialize(board, 4);
	printboard(board, 1);

	solve(board);

	printboard(board, 1);
}

void solve(char board[ROWS][COLUMNS]) {
	while(falldown(board));
	printf("Game set. Can't find any more to crush.\n");
}

bool falldown(char board[ROWS][COLUMNS]) {
	bool flag = false;
	bool temp[PLAYINGHEIGHT][COLUMNS] = { 0 };
	for (int j = PLAYINGHEIGHT - 1; j >= 0; j--) {
		for (int i = 0; i < COLUMNS; i++) {
			temp[j][i] = three_in_a_sequence(i, j, board);
		}
	}
	for (int j = PLAYINGHEIGHT - 1; j >= 0; j--) {
		for (int i = 0; i < COLUMNS; i++) {
			if (temp[j][i]) {
				if (!shiftarray(-1, &(board[0][i]), ROWS, COLUMNS)) {
					printf("Not enough heap memory!\n");
					exit(1);
				}
				else {
					flag = true;
				}
			}
		}
	}
	return flag;
}

bool shiftarray(int shift, char arr[], int length, int pointer_dist) {
	// discard out of bounds, and replace empty position with 0
	/* if we are passing columns of 2d array to this function then we need to set
	   the pointer_dist to be the widths of that grid */
	char* temp = (char*)malloc(length * sizeof(char));
	if (temp == NULL) {
		return false;
	}
	for (int i = 0; i < length; i++) {
		temp[i] = arr[i * pointer_dist];
	}
	for (int i = 0; i < length; i++) {
		if (0 <= i - shift && i - shift < length) {
			arr[i * pointer_dist] =temp[i-shift];
		}
		else {
			arr[i * pointer_dist] = '0';
		}
	}
	free(temp);
	return true;
}

bool three_in_a_sequence(int x, int y, char board[ROWS][COLUMNS]) {
	// return true if three in a sequence
	char diff[] = { 'x','y' };
	// choose which direction to be considered
	for (int c = 0; c < 2; c++) {
		int sx = diff[c] == 'x' ? 1 : 0;
		int sy = diff[c] == 'y' ? 1 : 0;
		for (int k = -2; k <= 0; k++) {
			// consider consecutive three
			int x1 = x + k * sx;
			int y1 = y + k * sy;
			int x2 = x + (k + 1) * sx;
			int y2 = y + (k + 1) * sy;
			int x3 = x + (k + 2) * sx;
			int y3 = y + (k + 2) * sy;
			if (is_in_board(x1,y1) && is_in_board(x3,y3)\
				&& is_in_play_area(x1,y1) && is_in_play_area(x3,y3)\
				&& board[y1][x1]==board[y2][x2]\
				&& board[y1][x1] == board[y3][x3]) {
				return true;
			}
		}
	}
	return false;
}

void random_initialize(char board[ROWS][COLUMNS], int colours) {
	for (int j = ROWS - 1; j >= 0; j--) {
		for (int i = 0; i < COLUMNS; i++) {
			board[j][i] = 'A' + rand() % colours;
		}
	}
}

void printboard(char board[ROWS][COLUMNS], int mode) {
	// mode==0: print only the playing area
	// mode!=0: print all rows

	for (int j = mode == 0 ? PLAYINGHEIGHT - 1 : ROWS - 1; j >= 0; j--) {
		for (int i = 0; i < COLUMNS; i++) {
			printf("%s%c ", three_in_a_sequence(i,j,board)?RED:NRM, board[j][i]);
		}
		printf("%s\n",NRM);
	}
	printf("%s\n",NRM);
}

bool is_in_play_area(int x, int y) {
	return y < PLAYINGHEIGHT;
}

bool is_in_board(int x, int y) {
	return (0 <= x) && (x < COLUMNS) && (0 <= y) && (y < ROWS);
}

void test() {
	assert(is_in_board(0, 4));
	assert(!is_in_board(-1, 4));
	assert(!is_in_board(COLUMNS, 3));
	assert(!is_in_board(1, ROWS));
	assert(!is_in_board(0, -1));
	assert(is_in_play_area(0, PLAYINGHEIGHT-1));
	assert(!is_in_play_area(0, PLAYINGHEIGHT));
}
