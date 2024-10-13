#include<stdio.h>
#include<assert.h>
#include<unistd.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

#define ROWS 30
#define COLS 80

#define MAX_ITERATIONS 1000

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

bool probability(double p);
void randomise(char grid[ROWS][COLS],double p_tree);
void printgrid(char grid[ROWS][COLS]);
void setempty(char grid[ROWS][COLS],char temp[ROWS][COLS]);
void setfire_fire(char grid[ROWS][COLS],char temp[ROWS][COLS]);
void setfire_lightning(char grid[ROWS][COLS],char temp[ROWS][COLS],double p);
void grows(char grid[ROWS][COLS],char temp[ROWS][COLS],double p);
void copy(char dest[ROWS][COLS], char source[ROWS][COLS]);
void normal(char grid[ROWS][COLS],char temp[ROWS][COLS]);

int main(){
    srand(time(NULL));
    char grid[ROWS][COLS];
    char temp[ROWS][COLS]={0};
    randomise(grid,1);
    for(int i=0;i<MAX_ITERATIONS;i++){
        printgrid(grid);
        setempty(grid,temp);
        setfire_fire(grid,temp);
        setfire_lightning(grid,temp,1.0/2500.0);
        grows(grid,temp,1.0/250.0);
        normal(grid,temp);
        copy(grid,temp);
        usleep(20000);
    } 
} 

void copy(char dest[ROWS][COLS], char source[ROWS][COLS]){
    for(int j=0;j<ROWS;j++){
        for(int i=0;i<COLS;i++){
            dest[j][i]=source[j][i];
        }
    }
}

void setempty(char grid[ROWS][COLS],char temp[ROWS][COLS]){
    for(int j=0;j<ROWS;j++){
        for(int i=0;i<COLS;i++){
            if (grid[j][i]=='*'){
                temp[j][i]=' ';
            }
        }
    } 
}
void setfire_fire(char grid[ROWS][COLS],char temp[ROWS][COLS]){
    for(int j=0;j<ROWS;j++){
        for(int i=0;i<COLS;i++){
            if (grid[j][i]=='*'){
                for(int l=-1;l<=1;l++){
                    for(int k=-1;k<=1;k++){
                        bool inbound=!(k==0&&l==0) && 0<=i+k && i+k<COLS && 0<=j+l && j+l<ROWS;
                        if (inbound && grid[j+l][i+k]=='@'){
                            temp[j+l][i+k]='*';
                        }
                    }
                }
            }
        }
    }
}
void setfire_lightning(char grid[ROWS][COLS],char temp[ROWS][COLS],double p){
    for(int j=0;j<ROWS;j++){
        for(int i=0;i<COLS;i++){
            if (grid[j][i]=='@' && probability(p)){
                temp[j][i]='*';
            }
        }
    }
}
void grows(char grid[ROWS][COLS],char temp[ROWS][COLS],double p){
    for(int j=0;j<ROWS;j++){
        for(int i=0;i<COLS;i++){
            if (grid[j][i]==' ' && probability(p)){
                temp[j][i]='@';
            }
        }
    }
}

void normal(char grid[ROWS][COLS],char temp[ROWS][COLS]){
    for(int j=0;j<ROWS;j++){
        for(int i=0;i<COLS;i++){
            if (temp[j][i]=='\0' && grid[j][i]=='@'){
                temp[j][i]='@';
            }
            if (temp[j][i]=='\0' && grid[j][i]==' '){
                temp[j][i]=' ';
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
                grid[j][i]='@';
            }else{
                grid[j][i]=' ';
            }
        }
    }
}

void printgrid(char grid[ROWS][COLS]) {
    printf("\033[H\033[J");
    for (int j = 0; j < ROWS; j++) {
        for (int i = 0; i < COLS; i++) {
            if (grid[j][i] == '*') {
                printf("%s%c ", RED, '*');
            }else if (grid[j][i] =='@') {
                printf("%s%c ",GRN,'@');
            }else {
                printf("%s%c ", NRM, grid[j][i]);
            }
        }
        printf("%s\n", NRM);
    }
    printf("%s\n", NRM);
}
