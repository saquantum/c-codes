#include<stdio.h>
#include<stdlib.h>
#define A 9
#define C 5
#define M 11
#define LOOPS 10
#define SIZE 1000

void copyArrayIntoLarger(int arr0[],int len0,int arr[],int len);
int arrayCompare(int arr0[],int len0,int arr[],int len);

int main(){
    /*
    int i;
    int seed = 0;
    for(i=0; i<LOOPS; i++){
        seed = (A*seed + C) % M;
        printf("%d\n",seed);
    }
    */
    
    int testarr[]={1,2,3,4,5,1,2,6,7,8,9,1,2,3,4,5,1,2,6,7,8,9,1,2,3,4,5,1,2,6,7,8,9};
    int len0=1;
    int len1=0;
    int p0[20];
    int* p;
    
    int i=0;
    int num0=testarr[0];
    
    int flag;
    int period;
    
    while(1){
        *(p0+i)=testarr[i];
        i++;
        if (testarr[i]!=num0){
            len0++;
        }else {
            len1++;
            *(p+i)=testarr[i];
            i++;
            if (testarr[i]!=num0){
                flag=arrayCompare(p,len1,p0,len0);
                if (!flag){
                    period=len0;
                    break;
                }else{
                    len0+=len1;
                }
            }
            
        }
    }
    printf("%d",len0);
    
    
    
    return 0;
}

void copyArrayIntoLarger(int arr0[],int len0,int arr[],int len){
    int i=0;
    if (len>=len0){
    
        for (i=0;i<len0;i++){
            arr[i]=arr0[i];
        }
    }else {
        printf("new array is not larger than the original one exception");
    }
    
}

int arrayCompare(int arr0[],int len0,int arr[],int len){
    int i=0;
    if (len==len0){
        for (i=0;i<len0;i++){
            if (arr[i]!=arr0[i]){
                return 1;
            }
            
        }
        return 0;
    }else {
        return 1;
    }
}

