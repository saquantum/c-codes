#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

#define TILE 'X'
#define EMPTY '.'
#define STATES 2

#define HEIGHT 8
#define WIDTH 7
#define LISTSIZE 5000
#define LARGEPRIME 4999
#define INTERROR -1

typedef struct state{
    char board[HEIGHT][WIDTH];
    struct state* parent;
    int hash;
}state;

bool win(state* s, int x0, int y0);
bool inbound(int x, int y);
void childboards(state* parent, state** list, int* index, int x0, int y0, bool* found);
int hashcode(state* s);
bool equals(state* s1, state* s2);
void printboard(state* s, int x0, int y0);
void test();

int main(int argc, char** argv) {
    assert(argc==3);
    
    state* list[LISTSIZE];
    memset(list, 0, sizeof(list));
    
    char board[HEIGHT][WIDTH] = {
        {'.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X'}
    };
    state* init = malloc(sizeof(state));
    memcpy(init->board, board, sizeof(board));
    init->parent = NULL;
    init->hash = hashcode(init);
    
    int index=0;
    bool found=false;
    childboards(init, list, &index, atoi(argv[1]), atoi(argv[2]), &found);
    if(index>=LISTSIZE){
        printf("unable to find a solution.\n");
    }else{
        state* solution = list[index];
        printboard(solution,atoi(argv[1]), atoi(argv[2]));
    }
    free(init);
    for(int i=0;i<=index;i++){
        free(list[i]);
    }
}

bool win(state* s, int x0, int y0){
    if(s->board[y0][x0]==TILE){
        return true;
    }
    return false;
}

bool inbound(int x, int y){
    return 0<=x && x<WIDTH && 0<=y && y<HEIGHT;
}

void childboards(state* parent, state** list, int* index, int x0, int y0, bool* found){
    if(*index>=LISTSIZE){
        return;
    }
    // if other subtrees of recursion has found it, return immediately
    if(*found){
        return;
    }
    char* directions="udlr";
    for(int j=0;j<HEIGHT;j++){
        for(int i=0;i<WIDTH;i++){
            if(parent->board[j][i] == TILE){
                for(int k=0;k<(int)strlen(directions);k++){
                    int x1 = directions[k]=='l'?i-1:directions[k]=='r'?i+1:i;
                    int x2 = directions[k]=='l'?i-2:directions[k]=='r'?i+2:i;
                    int y1 = directions[k]=='d'?j-1:directions[k]=='u'?j+1:j;
                    int y2 = directions[k]=='d'?j-2:directions[k]=='u'?j+2:j;
                    if(inbound(x1,y2) && inbound(x2,y2) && parent->board[y1][x1] == TILE && parent->board[y2][x2] == EMPTY && !(*found)){
                        state* child = (state*)malloc(sizeof(state));
                        *child = *parent;
                        child->board[j][i] = EMPTY;
                        child->board[y1][x1] = EMPTY;
                        child->board[y2][x2] = TILE;
                        child->parent=parent;
                        child->hash=hashcode(child);
                        (*index)++;
                        list[*index]=child;
                        if(win(child,x0,y0)){
                            *found=true;
                        }
                        childboards(child, list, index, x0, y0, found);
                    }
                }
            }
        }
    }
    return;
}

int hashcode(state* s){
    if(!s){
        return INTERROR;
    }
    int hash=0;
    for(int j=0;j<HEIGHT;j++){
        for(int i=0;i<WIDTH;i++){
            hash = (hash*STATES+s->board[j][i])%LARGEPRIME;
        }
    }
    return hash;
}

bool equals(state* s1, state* s2){
    if(!s1 || !s2){
        return false;
    }
    if(s1->hash != s2->hash){
        return false;
    }
    for(int j=0;j<HEIGHT;j++){
        for(int i=0;i<WIDTH;i++){
            if(s1->board[j][i]!=s2->board[j][i]){
                return false;
            }
        }
    }
    return true;
}

void printboard(state* s, int x0, int y0){
    for(int j=0;j<HEIGHT;j++){
        for(int i=0;i<WIDTH;i++){
            if(i==x0 && j==y0){
                printf("%s%c ",RED,s->board[j][i]);
            }else{
                printf("%s%c ",NRM,s->board[j][i]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void test(){
    
}
