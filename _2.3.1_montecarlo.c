#include<stdio.h>
#include<math.h>
#include<assert.h>
#include<time.h>

#define LOOPS 1000
#define RADIUS 100

int main() {
    srand(time(NULL));
    int count = 0;
    int x = 0;
    int y = 0;
	
    for (int i = 0; i < LOOPS; i++) {
        x = rand()%(RADIUS);
        y = rand()%(RADIUS);
        if (x!=0 && y!=0 && x * x + y * y <= RADIUS * RADIUS) {
            count++;
        }
    }
    printf("pi is approxmately %lf", 4.0*(double)count / (double)LOOPS);
}
