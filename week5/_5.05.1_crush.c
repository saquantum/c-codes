#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define ROWS 20
#define COLUMNS 5
#define PLAYINGHEIGHT 6

void random_initialize(char board[ROWS][COLUMNS], int colours);
void printboard(char board[ROWS][COLUMNS], int mode);
bool is_in_play_area(int x, int y);
bool is_in_board(int x, int y);
void test();

int main() {

	test();

	srand(1);
	char board[ROWS][COLUMNS] = { 0 };
	random_initialize(board, 4);
	printboard(board, 1);
	
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
	
	for (int j =mode==0? PLAYINGHEIGHT -1:ROWS-1; j >=0; j--) {
		for (int i = 0; i < COLUMNS; i++) {
			printf("%c ", board[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

bool is_in_play_area(int x, int y) {
	return y < PLAYINGHEIGHT;
}

bool is_in_board(int x, int y) {
	return (0<=x) && (x< COLUMNS) && (0<=y) && (y<ROWS);
}

void test() {
	assert(is_in_board(0, 4));
	assert(!is_in_board(-1, 4));
	assert(is_in_board(0, 5));
	assert(!is_in_board(1, 20));
	assert(!is_in_board(0, -1));

}
