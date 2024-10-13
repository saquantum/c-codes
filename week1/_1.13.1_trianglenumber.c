#include<stdio.h>

int trinum(int N);

int main(){
    printf("%d\n",trinum(5));
    return 0;   
}

int trinum(int N){
    if (N>1){
        return N+trinum(N-1);
    }
   return 1;
}
