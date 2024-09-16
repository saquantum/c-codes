#include<stdio.h>
#include<math.h>
#include<assert.h>
#include<time.h>

int main() {
	double sum = 0;
	int dn = 1;
	int sign = 1;

	for (long i = 0; i < 100000000; i++) {
		sign = dn % 4 == 1 ? +1:-1;
		sum = sum + 4.0 * (double)sign / (double)dn;
		dn += 2;
	}

	printf("%.8lf", sum);
	return 0;

}
