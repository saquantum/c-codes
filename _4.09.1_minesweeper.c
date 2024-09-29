//define a new int to tell whether all the blocks are known (win indicator)
//define new function calcweight.

#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>

#define GRID_SIZE 10
#define MINES 10
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

int calcmines(int x, int y, char grid[GRID_SIZE][GRID_SIZE], char c);
void random_initialise_grid(int mines, char grid[GRID_SIZE][GRID_SIZE]);
bool rule1(int known_mines, int x,int y, char board[GRID_SIZE][GRID_SIZE]);
bool rule2(int* mines, int x,int y, char board[GRID_SIZE][GRID_SIZE]);
void randomclick(char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]);
void weightedclick(char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]);
void onestep(int* known_mines, char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]);
void printboard(char grid[GRID_SIZE][GRID_SIZE]);

int main(){
    char grid[GRID_SIZE][GRID_SIZE]={0};
    srand(time(NULL));
    random_initialise_grid(MINES,grid);
    printboard(grid);
    char board[GRID_SIZE][GRID_SIZE]={0};
    
    int mines=0;
    while(1){
        onestep(&mines,grid,board);
        printboard(board);
    }
    
}

void onestep(int* known_mines, char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]){
    weightedclick(grid,board);
    int count=0;
    do{
        for(int j=0;j<GRID_SIZE;j++){
        for(int i=0;i<GRID_SIZE;i++){
	        if(rule1(*known_mines,i,j,board)){
	            count++;
	        }
	        if(rule2(known_mines,i,j,board)){
	            count++;
	        }
        }
    }
    }while(count>0);
}

void randomclick(char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]){
    int x,y;
    while(board[x=rand()%GRID_SIZE][y=rand()%GRID_SIZE]!='\0');
    if (grid[x][y]=='x'){
        printf("you click a mine, game over.\n");
        exit(1);
    }else if('0'<=grid[x][y] && grid[x][y]<='8'){
        board[x][y]=grid[x][y];
    }else{
        printf("something went wrong.\n");
    }
    printf("x=%d,y=%d,grid[x][y]=%c\n",x,y,grid[x][y]);
}

void weightedclick(char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]){
    int x,y;
    int weight=8*8+1; // the highest possible weight plus one
    int temp;
    for(int i=0;i<GRID_SIZE;i++){
        for(int j=0;j<GRID_SIZE;j++){
            // calc weight
            weight=calcmines(i,j,grid,'x')*8+
            if(temp<weight){
                weight=temp;
                x=i;
                y=j;
            }
        }
    }
    if (grid[x][y]=='x'){
        printf("you click a mine, game over.\n");
        exit(1);
    }else if('0'<=grid[x][y] && grid[x][y]<='8'){
        board[x][y]=grid[x][y];
    }else{
        printf("something went wrong.\n");
    }
    printf("x=%d,y=%d,grid[x][y]=%c\n",x,y,grid[x][y]);
}

bool rule1(int known_mines, int x,int y, char board[GRID_SIZE][GRID_SIZE]){
    if (known_mines==MINES){
        board[x][y]=(char)(calcmines(x,y,board,'x')+'0');
        return true;
    }
    return false;
}

bool rule2(int* mines, int x,int y, char board[GRID_SIZE][GRID_SIZE]){
    int count=0;
    int unknown=calcmines(x,y,board,'\0');
    int known_mines=calcmines(x,y,board,'x');
    if (board[x][y]-'0'==unknown+known_mines && unknown>0){
        for(int i=-1;i<=1;i++){
            for(int j=-1;j<=1;j++){
                if( !(i==0&&j==0) && 0<=x+i && x+i<=GRID_SIZE-1 \
                && 0<=y+j && y+j<=GRID_SIZE-1 && board[x+i][y+j]=='\0'){
                    board[x+i][y+j]='x';
                    count++;
                }
            }
        }
    }
    *mines+=count;
    return count>0;
}

void random_initialise_grid(int mines, char grid[GRID_SIZE][GRID_SIZE]){
    int x,y;
    while(mines>0){
        x=rand()%GRID_SIZE;
        y=rand()%GRID_SIZE;
        if(grid[x][y]!='x'){
            grid[x][y]='x';
            mines--;
        }
    }
    for(int j=0;j<GRID_SIZE;j++){
        for(int i=0;i<GRID_SIZE;i++){
	        if (grid[i][j]!='x') {
                grid[i][j]=calcmines(i,j,grid,'x')+'0';
            }
        }
    }
}

int calcmines(int x, int y, char grid[GRID_SIZE][GRID_SIZE],char c){
    int count=0;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if( !(i==0&&j==0) && 0<=x+i && x+i<=GRID_SIZE-1 \
            && 0<=y+j && y+j<=GRID_SIZE-1 && grid[x+i][y+j]==c){
                count++;
            }
        }
    }
    return count;
}

void printboard(char grid[GRID_SIZE][GRID_SIZE]){
    for(int j=0;j<GRID_SIZE;j++){
        for(int i=0;i<GRID_SIZE;i++){
	        if (grid[i][j]=='x') {
                printf("%s%2c",RED,'x');
            }
            else {
                printf("%s%2c",NRM,grid[i][j]);
            }
        }
        printf("%s\n",NRM);
    }
}
