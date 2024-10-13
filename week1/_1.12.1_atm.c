#include<stdio.h>

int main(){
    int num=1;
    int remainder=0;
    while(num%20!=0){ // may as well use do...while
        printf("How much money would you like ? ");
        scanf("%d",&num);
        if (num%20==0){
            printf("OK , dispensing ...");
        }else{
            remainder=num%20;
            printf("I can give you %d or %d , try again .\n", \
            num-remainder,((num-remainder)/20+1)*20);
        }
    }
}
