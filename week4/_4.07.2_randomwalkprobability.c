#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>

#define PS 0.1
#define MAX_ITERATIONS 250
#define GRID_SIZE 50
#define X0 GRID_SIZE/2
#define Y0 GRID_SIZE/2
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

void random_walk_iteration(bool grid[GRID_SIZE][GRID_SIZE]);
void random_walk(int* px, int* py);
bool adjacent(int x, int y, bool grid[GRID_SIZE][GRID_SIZE]);

int main(){
	srand(time(NULL));
	bool grid[GRID_SIZE][GRID_SIZE]={0};
	grid[Y0][X0]=1;
	
	for (int i=0;i<MAX_ITERATIONS;i++){
	    random_walk_iteration(grid);
	}
	
	for(int j=0;j<GRID_SIZE;j++){
	    for(int i=0;i<GRID_SIZE;i++){
	        if (grid[j][i]==1) {
                printf("%s1 ",RED);
            }
            else {
                printf("%s0 ",NRM);
            }
	    }
	    printf("\n");
	}
}

void random_walk_iteration(bool grid[GRID_SIZE][GRID_SIZE]){
    int x0,y0;
    // find an unoccupied cell
    while(grid[y0=rand()%GRID_SIZE][x0=rand()%GRID_SIZE]);
    // and begin random walk
    while(!adjacent(x0,y0,grid) || rand()>RAND_MAX*PS){
        random_walk(&x0,&y0);
    }
    grid[y0][x0]=1;
}
void random_walk(int* px, int* py){
    int r;
    switch(r=rand()%4){
        case 0:
            *px=*px-1>=0?*px-1:GRID_SIZE-1;
            break;
        case 1:
            *px=*px+1<=GRID_SIZE-1?*px+1:0;
            break;
        case 2:
            *py=*py-1>=0?*py-1:GRID_SIZE-1;
            break;
        case 3:
            *py=*py+1<=GRID_SIZE-1?*py+1:0;
            break;
    }
}
bool adjacent(int x, int y, bool grid[GRID_SIZE][GRID_SIZE]){
    bool mid=(grid[y][x]==1);
    bool left=(grid[y][x-1>=0?x-1:GRID_SIZE-1]==1);
    bool right=(grid[y][x+1<=GRID_SIZE-1?x+1:0]==1);
    bool up=(grid[y+1<=GRID_SIZE-1?y+1:0][x]==1);
    bool down=(grid[y-1>=0?y-1:GRID_SIZE-1][x]==1);
    return mid || left || right || up || down;
}
