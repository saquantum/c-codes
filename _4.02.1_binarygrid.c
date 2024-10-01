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

struct board {
   char b2d[MAX][MAX];
   int sz;
};
typedef struct board board;

void test(void);
bool str2board(board* b, char* str);
void board2str(char* str, board* brd);
// Given a board, apply all rules repatedly - return true if solved, false otherwise
bool solve_board(board* brd);
bool pairs(board* brd);
bool oxo(board* brd);
bool counting(board* brd);

void printboard(board* brd);



int main(void)
{

    test();
   
    board b;
    char str[BOARDSTR];
    
    assert(str2board(&b, "1...1...0.....00...1................"));
    printboard(&b);
    solve_board(&b);
    printboard(&b);
    board2str(str, &b);
    assert(strcmp(str, "101010100101010011011010101100010101")==0);
    printf("%s\n",str);
   
   return 0;
}

bool str2board(board* brd, char* str){
    if(str==NULL){
        return false;
    }
    if(strlen(str)<=0){
        return false;
    }
    int sz=(int)round(sqrt((double)strlen(str)));
    if(fabs( pow((double)sz,2.0) - (double)strlen(str) )>0.001){
        return false;
    }
    if(sz%2!=0){
        return false;
    }
    
    for(int j=0;j<MAX;j++){
        for(int i=0;i<MAX;i++){
            brd->b2d[j][i]=0;
        }
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
    for(int i=0;i<BOARDSTR;i++){
        str[i]=0;
    }
    for(int j=0;j<brd->sz;j++){
        for(int i=0;i<brd->sz;i++){
            *(str+j*brd->sz+i)=brd->b2d[j][i];
        }
    }
}

bool solve_board(board* brd){
    while(pairs(brd) || oxo(brd) || counting(brd));
    for(int j=0;j<brd->sz;j++){
        for(int i=0;i<brd->sz;i++){
            if(brd->b2d[j][i]=='.'){
                return false;
            }
        }
    }
    return true;
}
bool pairs(board* brd){
    bool flag=false;
    for(int j=0;j<brd->sz;j++){
        for(int i=0;i<brd->sz;i++){
            if(i+1<brd->sz && brd->b2d[j][i]!='.' && brd->b2d[j][i]==brd->b2d[j][i+1]){
                if (0<=i-1 && brd->b2d[j][i-1]=='.'){
                    brd->b2d[j][i-1]=brd->b2d[j][i]=='1'?'0':'1';
                    flag=true;
                }
                if (i+2<brd->sz && brd->b2d[j][i+2]=='.'){
                    brd->b2d[j][i+2]=brd->b2d[j][i]=='1'?'0':'1';
                    flag=true;
                }
            }
            if(j+1<brd->sz && brd->b2d[j][i]!='.' && brd->b2d[j][i]==brd->b2d[j+1][i]){
                if (0<=j-1 && brd->b2d[j-1][i]=='.'){
                    brd->b2d[j-1][i]=brd->b2d[j][i]=='1'?'0':'1';
                    flag=true;
                }
                if (j+2<brd->sz && brd->b2d[j+2][i]=='.'){
                    brd->b2d[j+2][i]=brd->b2d[j][i]=='1'?'0':'1';
                    flag=true;
                }
            }
        }
    }
    return flag;
}
bool oxo(board* brd){
    bool flag=false;
    for(int j=0;j<brd->sz;j++){
        for(int i=0;i<brd->sz;i++){
            if(i+2<brd->sz && brd->b2d[j][i]!='.' && brd->b2d[j][i]==brd->b2d[j][i+2] \
               && brd->b2d[j][i+1]=='.'){
                brd->b2d[j][i+1]=brd->b2d[j][i]=='1'?'0':'1';
                flag=true;
            }
            if(j+2<brd->sz && brd->b2d[j][i]!='.' && brd->b2d[j][i]==brd->b2d[j+2][i] \
               && brd->b2d[j+1][i]=='.'){
                brd->b2d[j+1][i]=brd->b2d[j][i]=='1'?'0':'1';
                flag=true;
            }
        }
    }
    return flag;
}
bool counting(board* brd){
    bool flag=false;
    
    for(int j=0;j<brd->sz;j++){
        int count0=0;
        int count1=0;
        for(int i=0;i<brd->sz;i++){
            if(brd->b2d[j][i]=='0'){
                count0++;
            }
            if(brd->b2d[j][i]=='1'){
                count1++;
            }
        }
        if( (count0==brd->sz/2 || count1==brd->sz/2) && count0+count1<brd->sz){
            for(int i=0;i<brd->sz;i++){
                if(brd->b2d[j][i]=='.'){
                    brd->b2d[j][i]=count1==brd->sz/2?'0':'1';
                    flag=true;
                }
            }
        }
    }
    
    for(int i=0;i<brd->sz;i++){
        int count0=0;
        int count1=0;
        for(int j=0;j<brd->sz;j++){
            if(brd->b2d[j][i]=='0'){
                count0++;
            }
            if(brd->b2d[j][i]=='1'){
                count1++;
            }
        }
        if( (count0==brd->sz/2 || count1==brd->sz/2) && count0+count1<brd->sz){
            for(int j=0;j<brd->sz;j++){
                if(brd->b2d[j][i]=='.'){
                    brd->b2d[j][i]=count1==brd->sz/2?'0':'1';
                    flag=true;
                }
            }
        }
    }
    
    
    return flag;
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
