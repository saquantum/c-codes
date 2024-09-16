#include<stdio.h>
#include<math.h>
#include<assert.h>
#include<time.h>

#define E 2.71828182845904523536

int main() {
	double err = 4;
	double approx = 0;

	int x = 0;
	int y = 0;

	for (long i = 1; i < 100000; i++) {
		for (long j = (long)((double)i*2.7); j <  (long)((double)i*2.8); j++) {
			approx = (double)j / (double)i;
			if (fabs(approx - E) < err) {
				x = i;
				y = j;
				err = fabs(approx - E);
			}
		}
	}
	printf("%d/%d=%.20lf",y,x,(double)y/(double)x);
	return 0;
}
