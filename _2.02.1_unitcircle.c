#include<stdio.h>
#include<math.h>
#include<assert.h>

#define ERR 1e-8

int unitcircle(double x);
void test();

int main() {
    test();
}

int unitcircle(double x) {
    return pow(sin(x), (double)2) + pow(cos(x), (double)2);
}

void test(){
    assert((unitcircle(0.2) - 1) < ERR);
    assert((unitcircle(-3) - 1) < ERR);
    assert((unitcircle(10) - 1) < ERR);
    assert((unitcircle(100) - 1) < ERR);
}
