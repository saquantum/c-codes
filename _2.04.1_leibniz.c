#include<stdio.h>
#include<math.h>
#include<assert.h>
#include<time.h>

#define LOOPS 100000000

int main() {
    double sum = 0;
    // dn stands for denominator
    int dn = 1;
    int sign = 1;

    for (long i = 0; i < LOOPS; i++) {
        sign = dn % 4 == 1 ? +1:-1;
        sum = sum + 4.0 * (double)sign / (double)dn;
        dn += 2;
    }

    printf("%.8lf", sum);
    return 0;

}
