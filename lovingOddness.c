#include<stdio.h>

int main(){
    int i;
    int num;
    int num1=0;
    int num2=0;
    
    while(1){
        printf("%s","How many odd numbers do you wish to enter? ");
        scanf("%d",&num);
        if(num>1){
            break;
        }
        printf("the number of inputs must be greater than 1 to find a maximum\n");
    }
    while(1){
        printf("%s%d%s","Enter ", num," odd numbers: ");
        scanf("%d",&num1);
        if (num1%2==1){
            break;
        }
        printf("Please enter an odd number");
    }
    
    
    for (i=1;i<num;i++){
        while(1){
        printf("%s","Enter the next odd number: ");
        scanf("%d",&num2);
        if (num2%2==1){
            break;
        }
        printf("Please enter an odd number\n");
    }
        
        num1=num1>num2?num1:num2;
    }
    printf("your maximum value is %d",num1);
    return 0;
}
