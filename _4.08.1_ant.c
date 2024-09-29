#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>

#define MAX_ITERATIONS 30
#define GRID_SIZE 16
#define X0 GRID_SIZE/2
#define Y0 GRID_SIZE/2
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

typedef struct block{
    int x;
    int y;
}block;

void iteration(block* prev, block* now, block* next, bool grid[GRID_SIZE][GRID_SIZE]);
int main(){
    bool grid[GRID_SIZE][GRID_SIZE]={0};
    block prev,now,next;
    prev.x=X0;
    prev.y=Y0;
    now.x=X0;
    now.y=Y0;
    next.x=0;
    next.y=0;
    char c;
    int count=0;
    while((c=getchar())!=EOF && count<MAX_ITERATIONS){
        iteration(&prev,&now,&next,grid);
        prev=now;
        now=next;
        count++;
        printf("prev.x=%d,prev.y=%d,now.x=%d,now.y=%d\n",prev.x,prev.y,now.x,now.y);
        
        for(int j=0;j<GRID_SIZE;j++){
	    for(int i=0;i<GRID_SIZE;i++){
	        if (grid[i][j]==1) {
                printf("%s1 ",RED);
            }
            else {
                printf("%s0 ",NRM);
            }
	    }
	    printf("\n");
	}
	printf("\n");
    }
    return 0;
}

void iteration(block* prev, block* now, block* next, bool grid[GRID_SIZE][GRID_SIZE]){
    if(now->x-prev->x==-1 && now->y-prev->y==0){ //leftward, now0->up, now1->down
        next->x=now->x;
        next->y=!grid[now->x][now->y]?now->y+1:now->y-1;
    }else if(now->x-prev->x==1 && now->y-prev->y==0){ //rightward, now0->down, now1->up
        next->x=now->x;
        next->y=!grid[now->x][now->y]?now->y-1:now->y+1;
    }else if(now->x-prev->x==0 && now->y-prev->y==1){ //upward, now0->right, now1->left
        next->x=!grid[now->x][now->y]?now->x+1:now->x-1;
        next->y=now->y;
    }else if(now->x-prev->x==0 && now->y-prev->y==-1){ //downward, now0->left, now1->right
        next->x=!grid[now->x][now->y]?now->x-1:now->x+1;
        next->y=now->y;
    }else if(now->x-prev->x==0 && now->y-prev->y==0){ // choose a random direction
        next->x=now->x+1;
        next->y=now->y;
    }else {
        printf("something went wrong.\n");
        exit(1);
    }
    grid[now->x][now->y]=!grid[now->x][now->y];
}
