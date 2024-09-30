#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define BIGSTR 1000
#define GRID 100

struct crossword {
    char arr[GRID][GRID];
    int sz;
};
typedef struct crossword crossword;

void test(void);

/*
   Convert a size (sz) & string (ip) into a crossword*
   White squares are ' ' or '.', black squares 'X' or '*'
*/
bool str2crossword(int sz, char* ip, crossword* cw);

// Convert crossword to string of across & down numbers
void getcluestring(const crossword* c, char* str);
bool isAcross(int x, int y, const crossword* c);
bool isDown(int x, int y, const crossword* c);


// Get percentage of empty squares that are shared between two clues
int getchecked(crossword c);


int main(void)
{
    test();
    char str[BIGSTR];
    crossword c;
    assert(str2crossword(5, "....X.XX.X.X......X.XX...", &c));
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 5; i++) {
            printf("%c ",c.arr[j][i]);
        }
        printf("\n");
    }
    getcluestring(&c, str);
    printf("%s\n", str);
    printf("%d\n", getchecked(c));

    return 0;
}

bool str2crossword(int sz, char* ip, crossword* cw) {
    if (ip == NULL) {
        return false;
    }
    if (sz < 0) {
        return false;
    }
    if (sz * sz != strlen(ip)) {
        return false;
    }
    cw->sz = sz;
    for (int j = 0; j < sz; j++) {
        for (int i = 0; i < sz; i++) {
            (*cw).arr[j][i] = *(ip+j*sz+i);
        }
    }
    return true;
}

void getcluestring(const crossword* c, char* str) {
    int arrA[BIGSTR] = { 0 };
    int arrD[BIGSTR] = { 0 };
    int posA = 0;
    int posD = 0;
    int count = 1;

    for (int j = 0; j < c->sz; j++) {
        for (int i = 0; i < c->sz; i++) {
            if (isAcross(i, j, c)) {
                arrA[posA] = count;
                posA++;
            }
            if (isDown(i, j, c)) {
                arrD[posD] = count;
                posD++;
            }
            if (isAcross(i, j, c) || isDown(i, j, c)) {
                count++;
            }
        }
    }

    snprintf(str, BIGSTR, "A");
    for (int i = 0; i < posA; i++) {
        snprintf(str + strlen(str), BIGSTR - strlen(str), "-%d", arrA[i]);
    }
    snprintf(str + strlen(str), BIGSTR - strlen(str), "|D");
    for (int i = 0; i < posD; i++) {
        snprintf(str + strlen(str), BIGSTR - strlen(str), "-%d", arrD[i]);
    }
}

bool isAcross(int x, int y, const crossword* c) {
    if ((c->arr[y][x]=='.' || c->arr[y][x]==' ') && (x - 1 < 0 || c->arr[y][x - 1] == 'X' || c->arr[y][x - 1] == '*')) {
        return x + 1 < c->sz && (c->arr[y][x + 1] == '.' || c->arr[y][x + 1] == ' ');
    }
    return false;
}

bool isDown(int x, int y, const crossword* c) {
    if ((c->arr[y][x] == '.' || c->arr[y][x] == ' ') && (y - 1 < 0 || c->arr[y-1][x] == 'X' || c->arr[y-1][x] == '*')) {
        return y + 1 < c->sz && (c->arr[y+1][x] == '.' || c->arr[y+1][x] == ' ');
    }
    return false;
}


int getchecked(crossword c) {
    int total = 0;
    int count = 0;
    for (int j = 0; j < c.sz; j++) {
        for (int i = 0; i < c.sz; i++) {
            if (c.arr[j][i] == ' ' || c.arr[j][i] == '.') {
                total++;
                int temp = 0;
                if ((j + 1 < c.sz && (c.arr[j + 1][i] == ' ' || c.arr[j + 1][i] == '.')) || (0 <= j - 1 && (c.arr[j - 1][i] == ' ' || c.arr[j - 1][i] == '.'))) {
                    temp++;
                }
                if ((i + 1 < c.sz && (c.arr[j][i + 1] == ' ' || c.arr[j][i + 1] == '.')) || (0 <= i - 1 && (c.arr[j][i - 1] == ' ' || c.arr[j][i - 1] == '.'))) {
                    temp++;
                }
                if (temp == 2) {
                    count++;
                }
            }
        }
    }
    return round(((double)count / (double)total)*100);
}

void test(void) {
    char str[BIGSTR];
    crossword c;

    // Invalid (string NULL)
    assert(!str2crossword(1, NULL, &c));
    // Invalid (crossword* NULL)
    assert(!str2crossword(2, "", NULL));
    // Invalid (size incorrect)
    assert(!str2crossword(-7, "..X....X.XX.X.X.XX.X......X..XX.XX.........XX.XX.", &c));
    // Invalid (string too short)
    assert(!str2crossword(7, "", &c));
    // Invalid (string too long)
    assert(!str2crossword(5, "..X....X.XX.X.X.XX.X......X..XX.XX.........XX.XX.", &c));
    // Invalid (size too large)
    assert(!str2crossword(500, "..X....X.XX.X.X.XX.X......X..XX.XX.........XX.XX.", &c));

     //Valid Crosswords 
    assert(str2crossword(3, ".........", &c));
    getcluestring(&c, str);
    assert(strcmp("A-1-4-5|D-1-2-3", str) == 0);
    // All squares are shared (checked)
    assert(getchecked(c) == 100);

    //// Example from handout
    assert(str2crossword(5, "....X.XX.X.X......X.XX...", &c));
    getcluestring(&c, str);
    assert(strcmp("A-1-3-5-6|D-1-2-3-4", str) == 0);
    assert(getchecked(c) == 53);

    assert(str2crossword(5, "X...X...............X...X", &c));
    getcluestring(&c, str);
    assert(strcmp("A-1-4-6-7-8|D-1-2-3-4-5", str) == 0);
    assert(getchecked(c) == 100);

    // Can be ' ' and '*', not just '.' and 'X'
    assert(str2crossword(5, "*   *               *   *", &c));
    getcluestring(&c, str);
    assert(strcmp("A-1-4-6-7-8|D-1-2-3-4-5", str) == 0);
    assert(getchecked(c) == 100);

    assert(str2crossword(7, "..X....X.XX.X.X.XX.X......X..XX.XX.........XX.XX.", &c));
    getcluestring(&c, str);
    assert(strcmp("A-1-3-6-8|D-2-4-5-6-7", str) == 0);
    assert(getchecked(c) == 32);

    assert(str2crossword(7, "X.X........X.XX.X.X.X.......X.X.X.X....X.XX.X....", &c));
    getcluestring(&c, str);
    assert(strcmp("A-2-4-5-6-7|D-1-2-3", str) == 0);
    assert(getchecked(c) == 33);

    assert(str2crossword(7, "...X....X...X....X...X.XXX.X...X....X...X....X...", &c));
    getcluestring(&c, str);
    assert(strcmp("A-1-3-5-6-8-10-12-14-15-16|D-1-2-3-4-7-9-10-11-12-13", str) == 0);
    assert(getchecked(c) == 67);

    assert(str2crossword(7, "........X.XXX..X......X.X.X......X..XXX.X........", &c));
    getcluestring(&c, str);
    assert(strcmp("A-1-4-6-7|D-1-2-3-5", str) == 0);
    assert(getchecked(c) == 33);

    assert(str2crossword(8, ".....X.XX.X.X..........XX.X.X......X.X.XX..........X.X.XX.X.....", &c));
    getcluestring(&c, str);
    assert(strcmp("A-1-5-6-7-8-11-12-13|D-2-3-4-5-9-10", str) == 0);
    assert(getchecked(c) == 43);
}
