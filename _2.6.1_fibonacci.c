#include<stdio.h>
#include<math.h>
#include<assert.h>

#define PHI 1.61803398875
#define LOOPS 100

typedef enum bool{False, True} bool;
bool fibword_phi(int n);
void test();

int main(){
    test();
    for(int i=1;i<LOOPS;i++){
        printf("%d",fibword_phi(i));
    }
    return 0;
}

bool fibword_phi(int n){
    int temp=2+floor(n*PHI)-floor((n+1)*PHI);
    return (bool)temp;
}

void test(){
    assert(fibword_phi(1)==0);
    assert(fibword_phi(2)==1);
    assert(fibword_phi(3)==0);
    assert(fibword_phi(4)==0);
    assert(fibword_phi(5)==1);
    assert(fibword_phi(6)==0);
    assert(fibword_phi(7)==1);
    assert(fibword_phi(8)==0);
    assert(fibword_phi(9)==0);
    assert(fibword_phi(10)==1);
}
