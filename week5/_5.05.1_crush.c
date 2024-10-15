#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define ROWS 20
#define COLUMNS 5
#define PLAYINGHEIGHT 6
#define ALPHASIZE 26

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

#define EMPTY '.'
#define SHIFTING_LEFTWARDS_1 -1

typedef struct state {
    char board[ROWS][COLUMNS];
}state;
void clearboard(state* s);
bool file2buffer(FILE* fp, char* buffer);
bool str2board(state* s, const char* str);
int nonempty_line(const state* s);
bool shiftarray(int shift, char arr[], int length, int pointer_dist);
bool three_in_a_sequence(int x, int y, state* s);
bool is_in_play_area(int x, int y);
bool is_in_board(int x, int y);
void printboard(state* s, int mode);
char* arr2str(char* a, int length); // only use in tests

bool initialise(state* s, const char* str);
bool tostring(const state* s, char* str);
bool matches(state* s);
bool dropblocks(state* s);

void test(void);

int main(void)
{
    test();
}

bool initialise(state* s, const char* str) {
    // edge cases
    if (!s || !str) {
        return false;
    }
    int len = strlen(str);
    if (!len) {
        clearboard(s);
        return true;
    }
    // str is a file path:
    FILE* fp = fopen(str, "r");
    if (fp) {
        char buffer[ROWS * COLUMNS + 1] = { 0 };
        if (!file2buffer(fp, buffer)) {
            return false;
        }
        fclose(fp);
        return str2board(s, buffer);
    }
    // str is a board string:
    if (len % COLUMNS) {
        return false;
    }
    int k = 0;
    while (str[k]) {
        bool inboard = ('A' <= str[k] && str[k] <= 'Z') || str[k] == EMPTY;
        if (!inboard) {
            return false; // this also exclude cases of invalid filepath
        }
        k++;
    }
    return str2board(s, str);
}

void clearboard(state* s) {
    for (int j = 0; j < ROWS; j++) {
        for (int i = 0; i < COLUMNS; i++) {
            s->board[j][i] = EMPTY;
        }
    }
}

bool file2buffer(FILE* fp, char* buffer) {
    if (!fp || !buffer) {
        return false;
    }
    char c;
    int k = 0;
    while ((c = fgetc(fp)) != EOF) {
        bool inboard = ('A' <= c && c <= 'Z') || c == EMPTY;
        bool isauxchar = c == ' ' || c == '\n' || c == '\r';
        bool isvalid = inboard || isauxchar;
        if (!isvalid) {
            //printf("invalid character detected in your input file.\n");
            return false;
        }
        if (inboard) {
            buffer[k] = c;
            k++;
        }
    }
    return true;
}

bool str2board(state* s, const char* str) {
    if (!s || !str) {
        return false;
    }
    int l = strlen(str);
    if (l > ROWS * COLUMNS) {
        //printf("Your input string is too long and exceeds the maximum size of the board. However I will proceed anyway but only part of the string will be put into the board.\n");
    }
    l--; // bypass the ending null character
    for (int j = 0; j < ROWS; j++) {
        for (int i = COLUMNS - 1; i >= 0; i--) {
            if (l >= 0) {
                s->board[j][i] = str[l];
                l--;
            }
            else {
                s->board[j][i] = EMPTY;
            }
        }
    }
    return true;
}

bool tostring(const state* s, char* str) {
    if (!s || !str) {
        return false;
    }
    int line = nonempty_line(s);
    int k = 0;
    // starting from the first non empty line from above
    for (; k < (line + 1) * COLUMNS; k++) {
        int j = line - k / COLUMNS;
        int i = k % COLUMNS;
        str[k] = s->board[j][i];
    }
    str[k] = '\0';
    return true;
}

int nonempty_line(const state* s) {
    if (!s) {
        return -1;
    }
    for (int j = ROWS - 1; j >= 0; j--) {
        int countempty = 0;
        for (int i = 0; i < COLUMNS; i++) {
            countempty = s->board[j][i] == EMPTY ? countempty + 1 : countempty;
        }
        if (countempty < COLUMNS) {
            return j;
        }
    }
    return -1;
}

bool matches(state* s) {
    if (!s) {
        return false;
    }
    bool flag = false;
    bool temp[PLAYINGHEIGHT][COLUMNS] = { 0 };
    for (int j = PLAYINGHEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < COLUMNS; i++) {
            temp[j][i] = three_in_a_sequence(i, j, s);
        }
    }
    for (int j = PLAYINGHEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < COLUMNS; i++) {
            if (temp[j][i]) {
                s->board[j][i] = EMPTY;
                flag = true;
            }
        }
    }
    return flag;
}

bool dropblocks(state* s) {
    if (!s) {
        return false;
    }
    bool flag = false;
    for (int j = PLAYINGHEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < COLUMNS; i++) {
            if (s->board[j][i] == EMPTY) {
                /* ROWS-j is the length or height above current cell
                   combining SHIFTING_LEFTWARDS_1 = -1 and COLUMNS
                   we are shifting column upwards by 1 cell */
                if (!shiftarray(SHIFTING_LEFTWARDS_1, &(s->board[j][i]), ROWS - j, COLUMNS)) {
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
    // discard out of bounds, and replace empty position with EMPTY
    /* we are passing columns of 2d array to this function so we need to set
       the pointer_dist to be the widths of that grid */
    if (!arr) {
        return false;
    }
    char* temp = (char*)malloc(length * sizeof(char));
    if (temp == NULL) {
        return false;
    }
    for (int i = 0; i < length; i++) {
        temp[i] = arr[i * pointer_dist];
    }
    for (int i = 0; i < length; i++) {
        if (0 <= i - shift && i - shift < length) {
            arr[i * pointer_dist] = temp[i - shift];
        }
        else {
            arr[i * pointer_dist] = EMPTY;
        }
    }
    free(temp);
    return true;
}

/* this function is from my own 4.02.1_binarygrid code,
i don't know if i need to cite this, anyway, now i've cited. */
bool three_in_a_sequence(int x, int y, state* s) {
    if (!s) {
        return false;
    }
    // return true if three in a sequence
    char* diff = "xy";
    // choose which direction to be considered
    for (int c = 0; c < (int)strlen(diff); c++) {
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
            if (is_in_play_area(x1, y1) && is_in_play_area(x3, y3)\
                && s->board[y1][x1] != EMPTY \
                && s->board[y1][x1] == s->board[y2][x2]\
                && s->board[y1][x1] == s->board[y3][x3]) {
                return true;
            }
        }
    }
    return false;
}

bool is_in_play_area(int x, int y) {
    return is_in_board(x, y) && y < PLAYINGHEIGHT;
}

bool is_in_board(int x, int y) {
    return (0 <= x) && (x < COLUMNS) && (0 <= y) && (y < ROWS);
}

void printboard(state* s, int mode) {
    if (!s) {
        return;
    }
    // mode==0: print only the playing area
    // mode!=0: print all rows
    for (int j = mode == 0 ? PLAYINGHEIGHT - 1 : ROWS - 1; j >= 0; j--) {
        for (int i = 0; i < COLUMNS; i++) {
            printf("%s%2c", three_in_a_sequence(i, j, s) ? RED : NRM, s->board[j][i]);
        }
        printf("%s\n", NRM);
    }
    printf("%s\n", NRM);
}

char* arr2str(char* a, int length) { // must use with "free"!
    if (!a || length < 0) {
        return NULL;
    }

    char* out = (char*)malloc(sizeof(char) * (length + 1));
    if (!out) {
        return NULL;
    }
    for (int i = 0; i < length; i++) {
        out[i] = a[i];
    }
    out[length] = '\0';
    return out;
}

void test(void) {
    state s;

    assert(!initialise(&s, "~/i_believe_this_file_does_not_exist.txt"));

    assert(initialise(&s, "....."));
    assert(dropblocks(&s));

    assert(initialise(&s, ""));

    assert(!initialise(&s, "ABC"));

    assert(!initialise(&s, "A!B-C*D&E..ABC."));

    assert(initialise(&s, "AAAAAAAAABAAAACAAAADAAAAEAAAAFAAAAGAAAAHAAAAIAAAAJAAAAKAAAAL\
AAAAMAAAANAAAAOAAAAPAAAAQAAAARAAAASAAAATAAAAUAAAAVAAAAWAAAAXAAAAYAAAAZ"));
    char tmp[200] = { 0 };
    assert(tostring(&s, tmp));
    assert(strlen(tmp) == ROWS * COLUMNS);
    assert(!strcmp(tmp, "AAAAGAAAAHAAAAIAAAAJAAAAKAAAALAAAAMAAAANAAAAOAAAAP\
AAAAQAAAARAAAASAAAATAAAAUAAAAVAAAAWAAAAXAAAAYAAAAZ"));

    assert(initialise(&s, "..............."));
    assert(nonempty_line(&s) == -1);

    assert(initialise(&s, "...............ABCDE"));
    assert(nonempty_line(&s) == 0);

    assert(initialise(&s, "...............ABCDE....."));
    assert(nonempty_line(&s) == 1);

    assert(initialise(&s, "...............A.C.E.........."));
    assert(nonempty_line(&s) == 2);

    char* str = "ABBBCABBBCABBCCABBBCABBBDABBBDABBBBAAABB";
    char tmpstr1[100] = { 0 };
    assert(str2board(&s, str));
    assert(tostring(&s, tmpstr1));
    assert(!strcmp(str, tmpstr1));

    assert(initialise(&s, str));
    for (int k = 0; k < (int)strlen(str); k++) {
        int i = k % COLUMNS;
        int j = strlen(str) / COLUMNS - k / COLUMNS - 1;
        assert(str[k] == s.board[j][i]);
    }

    assert(three_in_a_sequence(0, 0, &s) == true);
    assert(three_in_a_sequence(4, 0, &s) == false);
    assert(three_in_a_sequence(4, 1, &s) == true);
    assert(three_in_a_sequence(4, 2, &s) == false);
    assert(three_in_a_sequence(3, 3, &s) == true);
    assert(three_in_a_sequence(4, 5, &s) == false);

    char tmpstr2[100] = { 0 };
    assert(str2board(&s, ""));
    assert(tostring(&s, tmpstr2));
    assert(!strcmp(tmpstr2, ""));

    char tmpstr3[100] = { 0 };
    assert(str2board(&s, ".....A.C.E....."));
    assert(tostring(&s, tmpstr3));
    assert(!strcmp(tmpstr3, "A.C.E....."));

    char a[6] = { 0 };
    strcpy(a, "ABCDE");
    assert(shiftarray(-1, a, 5, 1));
    char* t1 = arr2str(a, 5);
    assert(!strcmp(t1, "BCDE."));
    free(t1);

    strcpy(a, "ABCDE");
    assert(shiftarray(2, a, 5, 1));
    char* t2 = arr2str(a, 5);
    assert(!strcmp(t2, "..ABC"));
    free(t2);

    strcpy(a, "ABCDE");
    assert(shiftarray(0, a, 5, 1));
    char* t3 = arr2str(a, 5);
    assert(!strcmp(t3, "ABCDE"));
    free(t3);

    char temp[5][5] = {
        {'A', 'B', 'C', 'D', 'E'},
        {'F', 'G', 'H', 'I', 'J'},
        {'K', 'L', 'M', 'N', 'O'},
        {'P', 'Q', 'R', 'S', 'T'},
        {'U', 'V', 'W', 'X', 'Y'}
    };
    assert(shiftarray(1, &(temp[0][0]), 5, 5));
    char* t4 = arr2str((char*)temp, 25);
    assert(!strcmp(t4, ".BCDEAGHIJFLMNOKQRSTPVWXY"));
    free(t4);

    str2board(&s, "ABBBC.........................");
    assert(matches(&s));

    str2board(&s, "ABBBC..............................");
    assert(!matches(&s));
}
