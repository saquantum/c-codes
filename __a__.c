#include<stdio.h>

int main(){
	int a, b = 0, c = 0;
	a = ++b + ++c; 
	printf("%i %i %i\n", a, b, c); //2 1 1
	a = b++ + c++;
	printf("%i %i %i\n", a, b, c); //2 2 2
	a = ++b + c++;
	printf("%i %i %i\n", a, b, c); //5 3 3
	a = b-- + --c;
	printf("%i %i %i\n", a, b, c); //5 2 2
}
