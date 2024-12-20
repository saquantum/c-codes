#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

// Maximum grid is 16x16
#define MAX  16
#define UNK  '.'
#define ONE  '1'
#define ZERO '0'
#define BOARDSTR (MAX*MAX+1)
#define MAX_TOLERANCE 0.001
#define ESCAPELOOP 1000

struct board {
    char b2d[MAX][MAX];
    int sz;
};
typedef struct board board;

void test(void);
bool str2board(board* b, char* str);
void board2str(char* str, board* brd);
void copyboard(board* dest, board* source);
bool solve_board(board* brd);
bool three_in_a_sequence(int x, int y, board* brd);
bool counting(int x, int y, board* brd);
bool recursion(int index, board* brd, board* temp, int* solutions);
void printboard(board* brd);

int main(void)
{
    test();

    return 0;
}

bool solve_board(board* brd) {
    int solutions = 0;
    board temp;
    copyboard(&temp, brd);
    return !recursion(0, brd, &temp, &solutions);
}

bool recursion(int index, board* brd, board* temp, int* solutions) {
    int sz = brd->sz;
    int x = index % sz;
    int y = index / sz;

    if (index >= sz * sz) { // escape recursion
        copyboard(brd, temp);
        (*solutions)++;
        if (*solutions > 1) {
            return true; // 2: for the second time we find a solution, it returns a true
        }
        return false; // 1: for the first time we find a solution, it returns a false
    }
    // skip an occupied cell 
    if (temp->b2d[y][x] != UNK) {
        return recursion(index + 1, brd, temp, solutions);
    }

    static char elements[] = { ZERO,ONE };
    for (int i = 0; i < 2; i++) {
        char guess = elements[i];
        temp->b2d[y][x] = guess;
        // check validity of current guess 
        if (three_in_a_sequence(x, y, temp) && counting(x, y, temp)) {
            /* go to the next guess
               1: since its a false, we wont go inside the following if
               2: now its a true, and we immediately finish current recursion by returning a true
                    and subsequently finish all parent recursions since we'll always go inside  */
            if (recursion(index + 1, brd, temp, solutions)) {
                if (*solutions > 1) {
                    return true;  // early escape in case of multiple solutions
                }
            }
        }
        // backtracking: reset the current cell and go back to its parent
        temp->b2d[y][x] = UNK;
    }
    // 0: if fails to find any solution
    return false;
}

void copyboard(board* dest, board* source) {
    int sz = source->sz;
    dest->sz = sz;
    for (int j = 0; j < sz; j++) {
        for (int i = 0; i < sz; i++) {
            dest->b2d[j][i] = source->b2d[j][i];
        }
    }
}

bool str2board(board* brd, char* str) {
    // edge cases
    if (str == NULL) {
        return false;
    }
    if (strlen(str) <= 0) {
        return false;
    }

    double sz_f = sqrt((double)strlen(str));
    // the size of the board must be an integer
    if ((fabs(sz_f - floor(sz_f))) > MAX_TOLERANCE || (fabs(sz_f - ceil(sz_f))) > MAX_TOLERANCE) {
        return false;
    }
    int sz = (int)round(sz_f);
    // the size of the board must be an even number to satisfy the counting rule
    if (sz % 2 != 0) {
        return false;
    }
    brd->sz = sz;
    for (int j = 0; j < sz; j++) {
        for (int i = 0; i < sz; i++) {
            brd->b2d[j][i] = str[j * sz + i];
        }
    }
    return true;
}

void board2str(char* str, board* brd) {
    int N = brd->sz;
    // edge cases
    if (N == 0) {
        str[0] = '\0';
        return;
    }
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            str[j * N + i] = brd->b2d[j][i];
        }
    }
    str[N * N] = '\0';
}

bool three_in_a_sequence(int x, int y, board* brd) {
    // return false if three in a sequence
    int sz = brd->sz;
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
            if (0 <= x1 && 0 <= y1 && x3 < sz && y3 < sz \
                && brd->b2d[y1][x1] != UNK \
                && brd->b2d[y1][x1] == brd->b2d[y2][x2] \
                && brd->b2d[y1][x1] == brd->b2d[y3][x3]) {
                return false;
            }
        }
    }
    return true;
}

bool counting(int x, int y, board* brd) {
    // return false if the numbers of zeros and ones in a line differ
    int sz = brd->sz;
    // count zeros and ones of that row and column
    int count0x = 0;
    int count1x = 0;
    int count0y = 0;
    int count1y = 0;
    for (int k = 0; k < sz; k++) {
        count0x = brd->b2d[y][k] == ZERO ? count0x + 1 : count0x;
        count1x = brd->b2d[y][k] == ONE ? count1x + 1 : count1x;
        count0y = brd->b2d[k][x] == ZERO ? count0y + 1 : count0y;
        count1y = brd->b2d[k][x] == ONE ? count1y + 1 : count1y;
    }
    if (count0x > sz / 2 || count1x > sz / 2 || count0y > sz / 2 || count1y > sz / 2) {
        return false;
    }
    return true;
}

void printboard(board* brd) {
    for (int j = 0; j < brd->sz; j++) {
        for (int i = 0; i < brd->sz; i++) {
            printf("%c ", brd->b2d[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

void test(void)
{
    board b;
    char str[BOARDSTR] = { 0 };

    assert(str2board(&b, "111..011.01.1001"));
    for (int j = 0; j < b.sz; j++) {
        for (int i = 0; i < b.sz; i++) {
            str[j * b.sz + i] = three_in_a_sequence(i, j, &b) + '0';
        }
    }
    assert(!strcmp(str, "0001100110011011"));

    for (int j = 0; j < b.sz; j++) {
        for (int i = 0; i < b.sz; i++) {
            str[j * b.sz + i] = counting(i, j, &b) + '0';
        }
    }
    assert(!strcmp(str, "0000100110011001"));

    // String Invalid
    assert(str2board(&b, "") == false);

    // Not an even size x even size board
    assert(str2board(&b, "...1.0...") == false);

    // An empty board still gives a 'sensible' string
    b.sz = 0;
    board2str(str, &b);
    assert(strcmp(str, "") == 0);

    // Solvable 2x2 Board
    assert(str2board(&b, ".0.."));
    assert(solve_board(&b) == true);
    board2str(str, &b);
    assert(strcmp(str, "1001") == 0);

    // Solvable 4x4 Board
    assert(str2board(&b, "...1.0......1..1"));
    assert(solve_board(&b) == true);
    board2str(str, &b);
    assert(strcmp(str, "0101101001101001") == 0);

    // Solvable4x4 Board
    assert(str2board(&b, "....0.0....1..0."));
    assert(solve_board(&b) == true);
    board2str(str, &b);
    assert(strcmp(str, "1010010100111100") == 0);

    // Unsolvable 4x4 Board
    assert(str2board(&b, "...1.0.........1"));
    assert(solve_board(&b) == false);

    // Solvable 6x6 Board
    assert(str2board(&b, "1...1...0.....00...1................"));
    assert(solve_board(&b) == true);
    board2str(str, &b);
    assert(strcmp(str, "101010100101010011011010101100010101") == 0);

    // Unsolvable 6x6 Board
    assert(str2board(&b, "....0...1.....11...0................"));
    assert(solve_board(&b) == false);

    // Solvable 8x8 Board
    assert(str2board(&b, "0.............0.00...1.....00.......0.....0..1.......00........."));
    assert(solve_board(&b) == true);
    board2str(str, &b);
    assert(strcmp(str, "0101011010011001001011010110011010010011110011000110100110110010") == 0);

}
