#include<stdio.h>
int main(){
	int a,b,c;
	printf("%s","input a integer");
	scanf("%d",&a);
	printf("%s","input a integer");
	scanf("%d",&b);
	printf("%s","input a integer");
	scanf("%d",&c);
	printf("%s%d %d %d","Input three integers: ",a,b,c);
	printf("Twice the sum of integers plus %d is %d !",7,7+(a+b+c)*2);
}
