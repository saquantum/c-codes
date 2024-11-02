#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

#define QUEEN 'X'
#define EMPTY '.'

#define SIZE 8
#define LISTSIZE 200000
#define INTERROR -1

typedef struct state {
    char board[SIZE][SIZE];
    int queens;
    char str[SIZE];
    struct state* parent;
}state;

void childboards(state* parent, state** list, int* index);
bool check(state* s, int x, int y);
int exists(state* s, state** list, int index);
bool equals(state* s1, state* s2);
void updatestr(state* s);
void printboard(state* s);
void test();

int main(void) {

    state** list=calloc(LISTSIZE,sizeof(state*));
    state* init = malloc(sizeof(state));
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            init->board[j][i] = EMPTY;
        }
    }
    init->queens = 0;
    init->parent = NULL;

    list[0] = init;
    int index = 1;
    bool found = false;

    for (int i = 0; i < index && index < LISTSIZE && !found; i++) {
        state* current = list[i];
        childboards(current,list,&index);
    }

    for (int i = 0; i < index; i++) {
        free(list[i]);
    }
}

void childboards(state* parent, state** list, int* index) {
    if (*index >= LISTSIZE) {
        return;
    }
    int next_row = parent->queens;  // Determine the next row based on number of queens placed
    if (next_row >= SIZE) {
        return;  // All queens placed, no further child states needed
    }
        for (int i = 0; i < SIZE; i++) {
            if (check(parent, i, next_row)) {
                state* child = (state*)malloc(sizeof(state));
                if (!child) {
                    return;
                }
                *child = *parent;
                child->board[next_row][i] = QUEEN;
                (child->queens)++;
                updatestr(child);
                child->parent = parent;
                if (exists(child, list, *index) == *index) {
                    list[*index] = child;
                    (*index)++;
                    if (child->queens==SIZE) {
                        printboard(child);
                    }
                }
                else {
                    free(child);
                }
            } 
        }
}

bool check(state* s, int x, int y) {
    char* dr = {"quprmdzl"};
    for (int n = 0; n < (int)strlen(dr); n++) {
        for (int k = 1; k < SIZE; k++) {
            int xn = dr[n] == 'p' || dr[n] == 'r' || dr[n] == 'm' ? x + k : dr[n] == 'q' || dr[n] == 'l' || dr[n] == 'z' ? x - k : x;
            int yn = dr[n] == 'q' || dr[n] == 'u' || dr[n] == 'p' ? y + k : dr[n] == 'z' || dr[n] == 'd' || dr[n] == 'm' ? y - k : y;
            if (0 <= xn && xn < SIZE && 0 <= yn && yn < SIZE && s->board[yn][xn] == QUEEN) {
                return false;
            }
        }
    }
    return true;
}

int exists(state* s, state** list, int index) {
    if (!s || !list) {
        return INTERROR;
    }
    for (int k = 0; k < index; k++) {
        if (equals(s, list[k])) {
            return k;
        }
    }
    return index;
}

bool equals(state* s1, state* s2) {
    if (!s1 || !s2) {
        return false;
    }
    if (s1->queens != s2->queens) {
        return false;
    }
    return memcmp(s1->str, s2->str, SIZE * sizeof(char)) == 0;
}

void updatestr(state* s) {
    for (int j = 0; j < SIZE; j++) {
        s->str[j] = -1;
        for (int i = 0; i < SIZE; i++) {
            if (s->board[j][i] == QUEEN) {
                s->str[j] = i;
            }
        }
    }
}

void printboard(state* s) {
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            printf("%c ", s->board[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

void test() {

}
