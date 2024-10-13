#include<stdio.h>
#include<stdlib.h>
#define A 9
#define C 5
#define M 11
#define LOOPS 15
#define SIZE 1000

/* UNFINISHED CODE
    */


void arrayCat(int arr1[],int len1,int arr2[],int len2,int* out);
int arrayCompare(int arr0[],int len0,int arr[],int len);

int main(){
int testarr[]={1,2,3,4,5,1,2,6,7,8,9,1,2,3,4,5,1,2,6,7,8,9,1,2,3,4,5,1,2,6,7,8,9};
    int len0=1;
    int len1=0;
    int p0[20]={0};
    int p[20]={0};
    
    int i=1;
    int num0=testarr[0];
    p0[0]=num0;
    
    int flag=1;
    int temp=1;
    int procedure=0;
    int period=0;
    int counter=0;
    
    while(flag && counter<LOOPS){
    counter++;
        // if num0 appears, then move in to the next procedure, else we put elements into array p0 as a buffer and modify the length of p0 by 1
        if (testarr[i]!=num0 && procedure==0){
            *(p0+i)=testarr[i];
            len0++;
            
            printf("test1, i is: %d, len0 is: %d, element is : %d\n",i+1,len0,p0[i]);
            i++;
        }else {
            // turn on this procedure
            procedure=1;
            // put elements in another new array p from now on
            while(temp){
                *(p+i)=testarr[i];
                len1++;
                printf("test2, i is: %d, len1 is: %d, element is : %d\n",i+1,len1,p[i]);
                i++;
                if (testarr[i]==num0){
                    temp=0;
                }
            }
            // if we encounter num0 again, test whether the two arrays p and p0 are the same
            if (testarr[i]==num0){
                
                flag=arrayCompare(p,len1,p0,len0);
                printf("test3, flag is %d, temp is %d\n",flag,temp);
                // p and p0 are the same, then we have the period
                if (!flag){
                    period=len0;
                    printf("test4\n");
                }else{
                    printf("test5\n");
                    arrayCat(p0,len0,p,len1,p0);
                    len0+=len1;
                    len1=0;
                    // turn off the procedure
                    procedure=0;
                }
            }
        }
    }
    printf("period is %d, flag is %d",len0,flag);
    return 0;
}

void arrayCat(int arr1[],int len1,int arr2[],int len2,int* out){
    //concatenate arrays arr1 and arr2 into out
    int i=0;
    for (;i<len1+len2;i++){
        if (i<len1){
            *(out+i)=arr1[i];
        }else{
            *(out+i)=arr2[i-len1];
        }
    }
}

int arrayCompare(int arr0[],int len0,int arr[],int len){
    // if the two arrays are the same, return 0
    int i=0;
    if (len!=len0){
        return 1;
    }
    for (i=0;i<len0;i++){
        if (arr[i]!=arr0[i]){
            return 1;
        }
    }
    return 0;
}
