#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>

#define MAX_ITERATIONS 10
#define GRID_SIZE 50
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

typedef struct cell{
    int x;
    int y;
}cell;

void iteration(int* ptr, bool grid[GRID_SIZE][GRID_SIZE], cell pos[MAX_ITERATIONS]);
bool stick(int x, int y, int* ptr, bool grid[GRID_SIZE][GRID_SIZE], cell pos[MAX_ITERATIONS]);

int main(){
	srand(time(NULL));
	bool grid[GRID_SIZE][GRID_SIZE]={0};
	grid[25][25]=1;
	cell pos[MAX_ITERATIONS];
	cell newcell;
	newcell.x=25;
	newcell.y=25;
	pos[0]=newcell;
    int N=1;
	for (int i=0;i<MAX_ITERATIONS;i++){
	    iteration(&N, grid, pos);
	}
	for(int j=0;j<GRID_SIZE;j++){
	    for(int i=0;i<GRID_SIZE;i++){
	        if (grid[i][j]==1) {
                printf("%s1 ",RED);
            }
            else {
                printf("%s0 ",NRM);
            }
	    }
	}
}

void iteration(int* ptr, bool grid[GRID_SIZE][GRID_SIZE], cell pos[MAX_ITERATIONS]){
    /* the pointer refers to the current living cells, or the total number of iterations
       the eligible length of pos must be *ptr */
    int r;
    while((r=rand()/(*ptr))+1 && !stick(pos[r].x, pos[r].y, ptr, grid, pos));
    
}

bool stick(int x, int y, int* ptr, bool grid[GRID_SIZE][GRID_SIZE], cell pos[MAX_ITERATIONS]){
    /* the input x and y refers to a currently existing cell 
       and we try to stick a new cell to a random existing cell, 
       if fails then do nothing */
    int adjacent4[4]={grid[x-1][y-1], grid[x-1][y+1], grid[x+1][y-1], grid[x+1][y+1]};
    int sum=0;
    int i;
    for(i=0;i<4;i++){
        sum+=adjacent4[i];
    }
       
    if (sum==4){
        return false; 
    }
    int newx;
    int newy;
    cell newcell;
    
    i=0;
    while(adjacent4[i]){
        i=rand()%4;
    }
    newx=(i/2)%2==0?x-1:x+1;
    newy=i%2==0?y-1:y+1;
    
    grid[newx][newy]=1;
    newcell.x=newx;
    newcell.y=newy;
    pos[*ptr]=newcell;
    (*ptr)++;
    return true;
}
