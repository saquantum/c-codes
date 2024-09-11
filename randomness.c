#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define max 100

int main(){
	int r;
	int less=0;
	int greater=0;
	int i;
	srand(time(NULL));
	for (i=0;i<50000;i++){
	    r=rand()%max;
	    if (r<max/2){
	        less++;
	    }else if(r>max/2){
	        greater++;
	    }
    }
    printf("%d\n",less-greater);
}
