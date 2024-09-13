#include<stdio.h>

int hs(int n);

int main(){
    int i=1;
    int max=1;
    int num=0;
    int temp=0;
    
    for(;i<10000;i++){
        temp=hs(i);
        if (max<temp){
            max=temp;
            num=i;
        }
    }
    printf("number %d has the longest sequence with length %d\n",num,max);

    return 0;
}

int hs(int n){
    int count=0;
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
