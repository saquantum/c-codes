#include<stdio.h>
#include<assert.h>

int is_prime(int n);
void test();

int main(){
    //test();
    int count=0;
    int n=1;
    while(count<3000){
        n++;
        if(!is_prime(n)){
            count++;
        }
    }
    printf("the %dth prime is %d\n",count,n);
    return 0;
}

int is_prime(int n){
    // output 0 indicates n is prime
    if (n<=2){
        return 0;
    }
    for(int i=2;i<n;i++){
        if (n%i==0){
            return 1;
        }
    }
    return 0;
}

void test(){
    assert(is_prime(1)==0);
    assert(is_prime(2)==0);
    assert(is_prime(3)==0);
    assert(is_prime(4)==1);
    assert(is_prime(5)==0);
    assert(is_prime(6)==1);
    assert(is_prime(7)==0);
    assert(is_prime(8)==1);
    assert(is_prime(9)==1);
    assert(is_prime(11)==0);
    
}
