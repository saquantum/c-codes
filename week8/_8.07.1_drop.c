#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

#define EMPTY '.'

#define HEIGHT 6
#define WIDTH 6
#define LISTSIZE 200000
#define INTERROR -1

typedef struct state{
    char board[HEIGHT][WIDTH];
    bool locked[WIDTH];
    char hawk;
    struct state* parent;
}state;

bool win(state* s);
void childboards(state* parent, state** list, int* index, bool* found);
bool push(state* s, int column);
void updatelocked(state* s);
int exists(state* s, state** list, int index);
bool equals(state* s1, state* s2);
void printboard(state* s);
void tracksteps(state* s);
void test();

int main(void) {

    state** list = calloc(LISTSIZE, sizeof(state*));
    if (!list) {
        return 1;
    }
    
    char board[HEIGHT][WIDTH] = {
        {'A', 'B', 'C', '.', '.', '.'},
        {'A', 'B', 'C', '.', '.', '.'},
        {'A', 'B', 'C', '.', '.', '.'},
        {'A', 'B', 'C', '.', '.', '.'},
        {'C', 'B', 'B', '.', '.', '.'},
        {'C', 'A', 'A', '.', '.', '.'}
    };
    bool locked[WIDTH]={0,0,0,1,1,1};
    state* init = malloc(sizeof(state));
    memcpy(init->board, board, sizeof(board));
    memcpy(init->locked, locked, sizeof(locked));
    init->hawk='A';
    init->parent = NULL;
    
    list[0] = init;
    int index = 1;
    bool found = false;
    
    for (int i = 0; i < index && index < LISTSIZE && !found; i++) {
        state* current = list[i];
        childboards(current, list, &index, &found);
        //printf("index=%d\n",index);
    }
    

    if(!found){
        printf("unable to find a solution.\n");
    }else{
        state* solution = list[index-1];
        //printboard(solution);
        tracksteps(solution);
    }
    
    for(int i=0;i<index;i++){
        free(list[i]);
    }
    free(list);

}

bool win(state* s){
    for(int i=0;i<WIDTH;i++){
        if(!s->locked[i]){
            return false;
        }
    }
    return true;
}

void childboards(state* parent, state** list, int* index, bool* found){
    if(!parent || !list || *index>=LISTSIZE){
        return;
    }
    if(*found){
        return;
    }
    for(int i=0;i<WIDTH;i++){
        state* child = (state*)malloc(sizeof(state));
        if (!child) {
            return;
        }
        *child = *parent;
        push(child, i); 
        updatelocked(child);
        child->parent=parent;
        
        if (exists(child, list, *index) == *index) { 
            list[*index] = child;
            (*index)++;
            if (win(child)) {
                *found = true;
                return;
            }
        } else {
            free(child); 
        }
        
        if(*found){
            return;
        }
    }
}

bool push(state* s, int column){
    if(!s){
        return false;
    }
    char newhawk=s->board[HEIGHT-1][column];
    for(int i=HEIGHT-1;i>0;i--){
        s->board[i][column]=s->board[i-1][column];
    }
    s->board[0][column]=EMPTY;
    for(int i=HEIGHT-1;i>=0;i--){
        if(s->board[i][column]==EMPTY){
            s->board[i][column]=s->hawk;
            s->hawk=newhawk;
            return true;
        }
    }
    return false;
}

void updatelocked(state* s){
    for(int i=0;i<WIDTH;i++){
        if(!s->locked[i]){
            bool locked=true;
            for(int j=1;j<HEIGHT && locked;j++){
                if(s->board[j-1][i]!=EMPTY && s->board[j][i]!=s->board[j-1][i]){
                    locked=false;
                }
            }
            s->locked[i]=locked;
        }
    }
}

int exists(state* s, state** list, int index){
    if(!s || !list){
        return INTERROR;
    }
    for(int k=0;k<index;k++){
        if(equals(s, list[k])){
            return k;
        }
    }
    return index;
}

bool equals(state* s1, state* s2){
    if(!s1 || !s2){
        return false;
    }
    if(s1->hawk!=s2->hawk){
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

void tracksteps(state* s){
    if(!s){
        return;
    }
    tracksteps(s->parent);
    printboard(s);
}

void printboard(state* s){
    printf("%c\n",s->hawk);
    for(int j=0;j<HEIGHT;j++){
        for(int i=0;i<WIDTH;i++){
                printf("%c ",s->board[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

void test(){
    
}
