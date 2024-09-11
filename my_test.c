#include<stdio.h>
#include<math.h>
int sumOfTwoNumbers(int num1, int num2);
int main(){
	int i,j,k;
	printf("%s","input an integer");
	scanf("%d",&j);
	i=1;
	k=sumOfTwoNumbers(i,j);
	//control string
	printf("%s%lf\n","the output is ",sqrt(k));
	return 0;
}

int sumOfTwoNumbers(int num1, int num2){
	return num1+num2;
}
