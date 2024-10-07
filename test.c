#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include<unistd.h>

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
bool solve_board(board* brd);
bool three_in_a_sequence(int x, int y, board* brd);
bool counting(int x, int y, board* brd);
bool win(board* brd);
void recursion(int index, board* brd);
void printboard(board* brd);

int main(void)
{

    //test();
   
    board b;
    char str[BOARDSTR];
    
    assert(str2board(&b, "1...1...0.....00...1................"));
    
    printf("Initial board:\n");
    printboard(&b);
    
    solve_board(&b);
    
    printf("Solved board:\n");
    printboard(&b);
    
    
    return 0;
}

bool str2board(board* brd, char* str){
    // edge cases
    if(str==NULL){
        return false;
    }
    if(strlen(str)<=0){
        return false;
    }
    
    double sz_f=sqrt((double)strlen(str));
    // the size of the board must be an integer
    if( (fabs(sz_f-floor(sz_f)))>MAX_TOLERANCE || (fabs(sz_f-ceil(sz_f)))>MAX_TOLERANCE){
        return false;
    }
    int sz=(int)round(sz_f);
    // the size of the board must be an even number to satisfy the counting rule
    if(sz%2!=0){
        return false;
    }
    brd->sz=sz;
    for(int j=0;j<sz;j++){
        for(int i=0;i<sz;i++){
            brd->b2d[j][i]=*(str+j*sz+i);
        }
    }
    return true;
}

void board2str(char* str, board* brd){
    int N=brd->sz;
    // edge cases
    if (N==0){
        str[0]='\0';
        return;
    }
    /* clear the string in O(N) time, or we could use 
       *(str+N*N)='\0' at the end of this function,
       which is not extremely clear but in O(1) time*/
    for(int i=0;i<BOARDSTR;i++){
        str[i]='\0';
    }
    for(int j=0;j<N;j++){
        for(int i=0;i<N;i++){
            *(str+j*N+i)=brd->b2d[j][i];
        }
    }
}

bool solve_board(board* brd){
    recursion(0, brd); 
    return win(brd);   
}

void recursion(int index, board* brd){
    int sz=brd->sz;
    
    if (index>=sz*sz) { // escape of recursion
        return;
    }
    // find current position in the 2d array
    int x=index%sz;
    int y=index/sz;
    
    if (brd->b2d[y][x]!=UNK) {
        recursion(index+1, brd);
        return;
    }
    
    for (char guess=ZERO; guess<=ONE; guess++) {
        brd->b2d[y][x]=guess;
        if (three_in_a_sequence(x, y, brd) && counting(x, y, brd)) {
            recursion(index+1, brd);
            if (win(brd)) return;
        }
        brd->b2d[y][x]=UNK;
    }
}

bool win(board* brd){
    for(int j=0;j<brd->sz;j++){
        for(int i=0;i<brd->sz;i++){
            if(brd->b2d[j][i]==UNK || !three_in_a_sequence(i,j,brd) || !counting(i,j,brd)){
                return false;
            }
        }
    }
    return true;
}

bool three_in_a_sequence(int x, int y, board* brd){
    // return false if three in a sequence
    int sz=brd->sz;
    if(0<=x-2 && brd->b2d[y][x]!=UNK && brd->b2d[y][x]==brd->b2d[y][x-2] && brd->b2d[y][x]==brd->b2d[y][x-1]){
        return false;
    }
    if(0<=x-1 && x+1<sz && brd->b2d[y][x]!=UNK \
        && brd->b2d[y][x]==brd->b2d[y][x-1] && brd->b2d[y][x]==brd->b2d[y][x+1]){
        return false;
    }
    if(x+2<sz && brd->b2d[y][x]!=UNK && brd->b2d[y][x]==brd->b2d[y][x+1] && brd->b2d[y][x]==brd->b2d[y][x+2]){
        return false;
    }
    if(0<=y-2 && brd->b2d[y][x]!=UNK && brd->b2d[y][x]==brd->b2d[y-2][x] && brd->b2d[y][x]==brd->b2d[y-1][x]){
        return false;
    }
    if(0<=y-1 && y+1<sz && brd->b2d[y][x]!=UNK \
        && brd->b2d[y][x]==brd->b2d[y-1][x] && brd->b2d[y][x]==brd->b2d[y+1][x]){
        return false;
    }
    if(y+2<sz && brd->b2d[y][x]!=UNK && brd->b2d[y][x]==brd->b2d[y+1][x] && brd->b2d[y][x]==brd->b2d[y+2][x]){
        return false;
    }
    return true;
}

bool counting(int x, int y, board* brd){
    int sz=brd->sz;
    int count0=0;
    int count1=0;
    for(int i=0;i<sz;i++){
        if(brd->b2d[y][i]==ZERO){
            count0++;
        }
        if(brd->b2d[y][i]==ONE){
            count1++;
        }
    }
    if(count0>sz/2 || count1>sz/2){
        return false;
    }
    count0=0;
    count1=0;
    for(int j=0;j<sz;j++){
        if(brd->b2d[j][x]==ZERO){
            count0++;
        }
        if(brd->b2d[j][x]==ONE){
            count1++;
        }
    }
    if(count0>sz/2 || count1>sz/2){
        return false;
    }
    return true;
}

void printboard(board* brd){
    for(int j=0;j<brd->sz;j++){
        for(int i=0;i<brd->sz;i++){
            printf("%c ",brd->b2d[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

void test(void)
{

    board b;
   char str[BOARDSTR];

   // String Invalid
   assert(str2board(&b, "")==false);

   // Not an even size x even size board
   assert(str2board(&b, "...1.0...")==false);

   // An empty board still gives a 'sensible' string
   b.sz = 0;
   board2str(str, &b);
   assert(strcmp(str, "")==0);
   
   // Solvable 2x2 Board
   assert(str2board(&b, ".0.."));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "1001")==0);

   // Solvable 4x4 Board
   assert(str2board(&b, "...1.0......1..1"));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "0101101001101001")==0);

   // Solvable4x4 Board
   assert(str2board(&b, "....0.0....1..0."));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "1010010100111100")==0);

   // Unsolvable 4x4 Board
   assert(str2board(&b, "...1.0.........1"));
   assert(solve_board(&b)==false);

   // Solvable 6x6 Board
   assert(str2board(&b, "1...1...0.....00...1................"));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "101010100101010011011010101100010101")==0);

   // Unsolvable 6x6 Board
   assert(str2board(&b, "....0...1.....11...0................"));
   assert(solve_board(&b)==false);

   // Solvable 8x8 Board
   assert(str2board(&b, "0.............0.00...1.....00.......0.....0..1.......00........."));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "0101011010011001001011010110011010010011110011000110100110110010")==0);

}
