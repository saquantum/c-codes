#include<stdio.h>
#include<math.h>
#include<assert.h>

int unitcircle(double x);

int main() {
	
	assert((unitcircle(0.2) - 1) < 0.00000001);
	assert((unitcircle(-3) - 1) < 0.00000001);
	assert((unitcircle(10) - 1) < 0.00000001);
	assert((unitcircle(100) - 1) < 0.00000001);
}

int unitcircle(double x) {
	return pow(sin(x), (double)2) + pow(cos(x), (double)2);
}
