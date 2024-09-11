#include<stdio.h>

int main(){
    int i;
    int num;
    double num1=0;
    double num2=0;
    
    while(1){
        printf("%s","How many numbers do you wish to enter? ");
        scanf("%d",&num);
        if(num>1){
            break;
        }
        printf("the number of inputs must be greater than 1 to find a maximum\n");
    }
    
    printf("%s%d%s","Enter ", num," real numbers: ");
    scanf("%lf",&num1);
    for (i=1;i<num;i++){
        printf("%s","Enter the next real numbers: ");
        scanf("%lf",&num2);
        num1=num1>num2?num1:num2;
    }
    printf("your maximum value is %.2lf",num1);
    return 0;
}
