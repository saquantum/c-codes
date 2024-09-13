#include<stdio.h>

int main(){
    int i;
    int num=0;
    int num1=2;
    int num2=2;
    
    while(num<=1 || num%2!=1){
        printf("%s","How many odd numbers do you wish to enter? ");
        scanf("%d",&num);
        if(num<=1){
            printf("the number of inputs must be greater than 1 to find a maximum\n");
        }
        if(num%2!=1){
            printf("the number of inputs is not an odd number\n");
        }
    }
    
    while(num1%2!=1){
        printf("%s","Enter the first odd number: ");
        scanf("%d",&num1);
        if (num1%2!=1){
            printf("Please enter an odd number, try again\n");
        }
    }
    
    
    for (i=1;i<num;i++){
        num2=2;
        while(num2%2!=1){
            printf("%s","Enter the next odd number: ");
            scanf("%d",&num2);
            if (num2%2!=1){
                printf("Please enter an odd number, try again\n");
            }
        }
        num1=num1>num2?num1:num2;
    }
    printf("your maximum value is %d",num1);
    return 0;
}
