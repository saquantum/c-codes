#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(){
	int r;
	int less=0;
	int greater=0;
	int i;
	srand(time(NULL));
	for (i=0;i<500;i++){
	    r=rand();
	    if (r<RAND_MAX/2){
	        less++;
	    }else if(r>RAND_MAX/2){
	        greater++;
	    }
    }
    printf("%d\n",less-greater);
}
