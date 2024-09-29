#include<stdio.h>
#include<assert.h>
int buttons(int seconds);
void test();
int main() {
    test();
    printf("%d",buttons(25));
    return 0;
}

int buttons(int seconds) {
    int sum = 0;
    int arr[3] = {600,60,10};
    seconds = seconds + (10 - seconds % 10);
    for (int i = 0; i < 3; i ++ ) {
        sum += seconds / arr[i];
        seconds -= (seconds / arr[i]) * arr[i];
    }
    return sum;
}
void test(){
    assert(buttons(705)==7);
    assert(buttons(25)==3);
    
}
