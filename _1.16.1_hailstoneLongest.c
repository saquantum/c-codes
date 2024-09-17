#include<stdio.h>
#include<assert.h>

#define LOOPS 10000000

long hs(long n);

int main(){
    long i=1;
    long max=1;
    long num=0;
    long temp=0;
    
    for(;i<LOOPS;i++){
        temp=hs(i);
        if (max<temp){
            max=temp;
            num=i;
        }
    }
    printf("number %ld has the longest sequence with length %ld\n",num,max);

    return 0;
}

long hs(long n){
    long count=0;
    while(n!=1){
        if(n%2==1){
            n=3*n+1;
        }else{
            n/=2;
        }
        //printf("%d ",n);
        count++;
    }
    return count;
}
