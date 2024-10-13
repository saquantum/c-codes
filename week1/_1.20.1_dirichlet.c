#include<stdio.h>
#include<assert.h>

int is_prime(int n);

int main(){
    //test();
    int count=0;
    int count3=0;
    int n=1;
    while(count<3000){
        n++;
        if(!is_prime(n)){
            count++;
            if(n%10==3){
                count3++;
            }
        }
        
    }
    printf("prime ends with 3 share a %.3lf fraction for the first %d primes",(double)count3/(double)count,count);
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
