#include<stdio.h>
#include<math.h>
#include<assert.h>
#include<time.h>

#define E 2.71828182845904523536
#define LOOPS 100000

int main() {
    /* must initialise the value of err(error) to be big enough 
	since there is a comparison in the loop */
    double err = 4;
    double approx = 0;

    int x = 0;
    int y = 0;

    for (int i = 1; i < LOOPS; i++) {
        // set the nested loop since e is between 2.7 and 2.8 to improve efficiency
        for (int j = (int)((double)i*2.7); j <  (int)((double)i*2.8); j++) {
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
