#include<stdio.h>
#include<assert.h>
#include<unistd.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

#define ROWS 20
#define COLS 20

#define MAX_ITERATIONS 1000

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

bool probability(double p);
void randomise(char grid[ROWS][COLS],double p_life);
void printgrid(char grid[ROWS][COLS]);
void copy(char dest[ROWS][COLS], char source[ROWS][COLS]);
void life(char grid[ROWS][COLS],char temp[ROWS][COLS]);

int main(){
    srand(time(NULL));
    char grid[ROWS][COLS];
    char temp[ROWS][COLS]={0};
    randomise(grid,0.3);
    for(int i=0;i<MAX_ITERATIONS;i++){
        printgrid(grid);
        life(grid,temp);
        copy(grid,temp);
        usleep(100000);
    } 
} 

void copy(char dest[ROWS][COLS], char source[ROWS][COLS]){
    for(int j=0;j<ROWS;j++){
        for(int i=0;i<COLS;i++){
            dest[j][i]=source[j][i];
        }
    }
}

void life(char grid[ROWS][COLS],char temp[ROWS][COLS]){
    for(int j=0;j<ROWS;j++){
        for(int i=0;i<COLS;i++){
            int count=0;
            for(int l=-1;l<=1;l++){
                for(int k=-1;k<=1;k++){
                    if(!(k==0&&l==0) && 0<=i+k && i+k<COLS \
                       && 0<=j+l && j+l<= ROWS && grid[j+l][i+k]=='1'){
                        count++;
                    }
                }
            }
            if(grid[j][i]=='1' && (count==2 || count==3)){
                temp[j][i]='1';
            }else if(grid[j][i]=='1' && (count<2 || 3<count)){
                temp[j][i]='0';
            }else if(grid[j][i]=='0' && 3<count){
                temp[j][i]='1';
            }else{
                temp[j][i]='0';
            }
        }
    }
}

bool probability(double p){
    if(p<0.0 || p>1.0){
        return false;
    }
    int r=rand();
    if((double)r/(double)RAND_MAX>p){
        return false;
    }
    return true;
}

void randomise(char grid[ROWS][COLS],double p_tree){
    for(int j=0;j<ROWS;j++){
        for(int i=0;i<COLS;i++){
            if (probability(p_tree)){
                grid[j][i]='1';
            }else{
                grid[j][i]='0';
            }
        }
    }
}

void printgrid(char grid[ROWS][COLS]) {
    printf("\033[H\033[J");
    for (int j = 0; j < ROWS; j++) {
        for (int i = 0; i < COLS; i++) {
            if (grid[j][i] == '1') {
                printf("%s%c ", RED, '1');
            }else if (grid[j][i] =='0') {
                printf("%s%c ",NRM,'0');
            }else {
                printf("%s%c ", NRM, grid[j][i]);
            }
        }
        printf("%s\n", NRM);
    }
    printf("%s\n", NRM);
}
