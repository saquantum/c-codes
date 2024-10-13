#include<stdio.h>
#include<assert.h>
#include<unistd.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

#define GRID_SIZE 5
#define MAX_ITERATIONS 1000

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"
#define NRM  "\x1B[0m"

void next(char grid[GRID_SIZE][GRID_SIZE],char temp[GRID_SIZE][GRID_SIZE]);
void printgrid(char grid[GRID_SIZE][GRID_SIZE]);
void copy(char dest[GRID_SIZE][GRID_SIZE], char source[GRID_SIZE][GRID_SIZE]);

int main(int argc, char **argv ){
    char grid[5][5]={{' ',' ',' ',' ',' '},{' ',' ',' ',' ',' '},{'H','c','c','c','c'},{' ',' ',' ',' ',' '},{' ',' ',' ',' ',' '}};
    char temp[GRID_SIZE][GRID_SIZE]={0};
    for(int i=0;i<MAX_ITERATIONS;i++){
        printgrid(grid);
        next(grid,temp);
        copy(grid,temp);
        usleep(1000000);
    } 
}

void next(char grid[GRID_SIZE][GRID_SIZE],char temp[GRID_SIZE][GRID_SIZE]){
    for(int j=0;j<GRID_SIZE;j++){
        for(int i=0;i<GRID_SIZE;i++){
            if (grid[j][i]==' '){
                temp[j][i]=' ';
            }
            if (grid[j][i]=='H'){
                temp[j][i]='t';
            }
            if (grid[j][i]=='t'){
                temp[j][i]='c';
            }
            if (grid[j][i]=='c'){
                int count=0;
                for(int l=-1;l<=1;l++){
                    for(int k=-1;k<=1;k++){
                        bool inbound=!(k==0&&l==0) && 0<=i+k && i+k<GRID_SIZE \
                        && 0<=j+l && j+l<GRID_SIZE;
                        if (inbound && grid[j+l][i+k]=='H'){
                            count++;
                        }
                    }
                }
                if(count==1 || count==2){
                    temp[j][i]='H';
                }else{
                    temp[j][i]='c';
                }
            }
        }
    } 
}

void copy(char dest[GRID_SIZE][GRID_SIZE], char source[GRID_SIZE][GRID_SIZE]){
    for(int j=0;j<GRID_SIZE;j++){
        for(int i=0;i<GRID_SIZE;i++){
            dest[j][i]=source[j][i];
        }
    }
}


void printgrid(char grid[GRID_SIZE][GRID_SIZE]) {
    printf("\033[H\033[J");
    for (int j = 0; j < GRID_SIZE; j++) {
        for (int i = 0; i < GRID_SIZE; i++) {
            if (grid[j][i] == 'H') {
                printf("%s%c ", RED, '*');
            }else if (grid[j][i] =='t') {
                printf("%s%c ",GRN,'*');
            }else if ( grid[j][i] =='c'){
                printf("%s%c ",YEL,'*');
            }else {
                printf("%s%c ", NRM, grid[j][i]);
            }
        }
        printf("%s\n", NRM);
    }
    printf("%s\n", NRM);
}
