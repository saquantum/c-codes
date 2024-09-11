#include<stdio.h>

int main(){
    int num;
    int remainder;
    while(1){
        printf("How much money would you like ? ");
        scanf("%d",&num);
        if (num%20==0){
            printf("OK , dispensing ...");
            break;
        }else{
            remainder=num%20;
            printf("I can give you %d or %d , try again .",num-remainder,((num-remainder)/20+1)*20);
        }
    }
}
