#include<stdio.h>
#define LOOPS 5

int main(){
    int num=100;
    int n=num-1; 
    int i=0;
    
    while(n!=num && i<LOOPS){
        printf("guess a number:");
        scanf("%d",&n);
        if (n==num){
            printf("correct\n");
        }else if(n>num){
            printf("too large\n");
        }else{
            printf("too small\n");
        }
        i++;
        if(i>=LOOPS){
            printf("no more chances to guess!\n");
        }
    }
}
