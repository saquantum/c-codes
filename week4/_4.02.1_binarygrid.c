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
    int i=0;
    while((pairs(brd) || oxo(brd) || counting(brd)) && i<ESCAPELOOP){
        i++;
    }
    if (i>=ESCAPELOOP){
        printf("Seems we've encountered an infinite loop and failed to solve the board.\n");
        return false;
    }
    // win condition
    for(int j=0;j<brd->sz;j++){
        for(int i=0;i<brd->sz;i++){
            if(brd->b2d[j][i]==UNK){
                return false;
            }
        }
    }
    return true;
}

bool pairs(board* brd){
    bool flag=false;
    int sz=brd->sz;
    for(int j=0;j<sz;j++){
        for(int i=0;i<sz;i++){
            /* for every cell, make sure no ArrayOutOfBounds: 0<=i-1, i+1<sz;
               and the current cell is not unoccupied: brd->b2d[j][i]!=UNK;
               and the adjacent two cells are the same. */
            if(i+1<sz && brd->b2d[j][i]!=UNK && brd->b2d[j][i]==brd->b2d[j][i+1]){ 
                // before the two cells
                if (0<=i-1 && brd->b2d[j][i-1]==UNK){
                    brd->b2d[j][i-1]=brd->b2d[j][i]==ONE?ZERO:ONE;
                    flag=true;
                }
                // after the two cells
                if (i+2<sz && brd->b2d[j][i+2]==UNK){
                    brd->b2d[j][i+2]=brd->b2d[j][i]==ONE?ZERO:ONE;
                    flag=true;
                }
            }
            if(j+1<sz && brd->b2d[j][i]!=UNK && brd->b2d[j][i]==brd->b2d[j+1][i]){
                if (0<=j-1 && brd->b2d[j-1][i]==UNK){
                    brd->b2d[j-1][i]=brd->b2d[j][i]==ONE?ZERO:ONE;
                    flag=true;
                }
                if (j+2<sz && brd->b2d[j+2][i]==UNK){
                    brd->b2d[j+2][i]=brd->b2d[j][i]==ONE?ZERO:ONE;
                    flag=true;
                }
            }
        }
    }
    return flag;
}

bool oxo(board* brd){
    bool flag=false;
    int sz=brd->sz;
    for(int j=0;j<sz;j++){
        for(int i=0;i<sz;i++){
            if(i+2<sz && brd->b2d[j][i]!=UNK && brd->b2d[j][i]==brd->b2d[j][i+2] \
               && brd->b2d[j][i+1]==UNK){
                brd->b2d[j][i+1]=brd->b2d[j][i]==ONE?ZERO:ONE;
                flag=true;
            }
            if(j+2<sz && brd->b2d[j][i]!=UNK && brd->b2d[j][i]==brd->b2d[j+2][i] \
               && brd->b2d[j+1][i]==UNK){
                brd->b2d[j+1][i]=brd->b2d[j][i]==ONE?ZERO:ONE;
                flag=true;
            }
        }
    }
    return flag;
}

bool counting(board* brd){
    bool flag=false;
    int sz=brd->sz;
    for(int j=0;j<sz;j++){
        int count0=0;
        int count1=0;
        // count rows
        for(int i=0;i<sz;i++){
            if(brd->b2d[j][i]==ZERO){
                count0++;
            }
            if(brd->b2d[j][i]==ONE){
                count1++;
            }
        }
        if( (count0==sz/2 || count1==sz/2) && count0+count1<sz){
            for(int i=0;i<sz;i++){
                if(brd->b2d[j][i]==UNK){
                    brd->b2d[j][i]=count1==sz/2?ZERO:ONE;
                    flag=true;
                }
            }
        }
    }
    
    for(int i=0;i<sz;i++){
        int count0=0;
        int count1=0;
        // count columns
        for(int j=0;j<sz;j++){
            if(brd->b2d[j][i]==ZERO){
                count0++;
            }
            if(brd->b2d[j][i]==ONE){
                count1++;
            }
        }
        if( (count0==sz/2 || count1==brd->sz/2) && count0+count1<sz){
            for(int j=0;j<sz;j++){
                if(brd->b2d[j][i]==UNK){
                    brd->b2d[j][i]=count1==sz/2?ZERO:ONE;
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
