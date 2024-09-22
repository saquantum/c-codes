#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define LENGTH 20
#define LOOPS 5000000

void randomswap(int a[LENGTH]);
void copyarray(const int current[LENGTH], int target[LENGTH]);
int sum(int a[LENGTH]);

int main() {
	srand(time(NULL));

	int i = 0;
	int a[LENGTH];
	for (i = 0; i < LENGTH; i++) {
		a[i] = i+1;
	}

	int temp[LENGTH];
	
	for (i = 0; i < LOOPS; i++) {
		copyarray(a,temp);
		randomswap(a);
		if (sum(a)>sum(temp)) {
			copyarray(temp, a);
		}
	}
	printf("total %d : ",sum(a));
	for (i = 0; i < LENGTH; i++) {
		printf("%d ",a[i]);
	}
	printf("\n");
}

void randomswap(int a[LENGTH]) {
	int i = rand()% LENGTH;
	int j = rand()% LENGTH;
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void copyarray(const int current[LENGTH], int target[LENGTH]) {
	for (int i = 0; i < LENGTH; i++) {
		target[i] = current[i];
	}
}

int sum(int a[LENGTH]) {
	int sum = 0;
	for (int i = 0; i < LENGTH; i++) {
		if (i == 0) {
			sum += (a[LENGTH - 1] + a[0] + a[1]) * (a[LENGTH - 1] + a[0] + a[1]);
		}
		else if (i == LENGTH - 1) {
			sum += (a[LENGTH - 2] + a[LENGTH - 1] + a[0]) * (a[LENGTH - 2] + a[LENGTH - 1] + a[0]);
		}
		else {
			sum += (a[i - 1] + a[i] + a[i + 1]) * (a[i - 1] + a[i] + a[i + 1]);
		}
	}
	return sum;
}
