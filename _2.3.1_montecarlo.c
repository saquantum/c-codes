#include<stdio.h>
#include<math.h>
#include<assert.h>
#include<time.h>

#define LOOPS 1000
#define RADIUS 100

int main() {
	srand(time(NULL));
	long count = 0;
	long x = 0;
	long y = 0;
	
	for (int i = 0; i < LOOPS; i++) {
		x = rand()%(RADIUS);
		y = rand()%(RADIUS);
		if (x!=0 && y!=0 && x * x + y * y <= RADIUS * RADIUS) {
			count++;
		}
	}

	printf("%lf", 4.0*(double)count / (double)LOOPS);

}
