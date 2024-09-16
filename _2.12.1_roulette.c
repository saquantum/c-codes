#include<stdio.h>
#include<time.h>

typedef enum bet{odd_even_bet,number_bet} bet;

int main(){
    char c;
    char a;
    int n=0;
    int count=0;
    
    printf("enter 0 or 1 to choose odd even bet or number bet");
    while((c=getchar)!='\n'){
        c=c%2;
    }
    printf();
    n=rand()%36;
    
    //printf("enter a number between 0 and 35");
    //while((a=getchar)!='\n'){}
    
}
