#include<stdio.h>

int main(){
    int num=100;
    
    for (int i=0;i<10;i++){
        int n; 
        printf("guess a number:");
        scanf("%d",&n);
        if (n==num){
            printf("correct");
            break;
        }else if(n>num){
            printf("too large");
        }else{
            printf("too small");
        }
    }
}
