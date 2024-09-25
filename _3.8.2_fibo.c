#include<stdio.h> 
#include<assert.h> 
#include<math.h>
#include<stdbool.h>

#define MAXSIZE 10000
#define PHI 1.61803

bool fibword_subs(int n);
bool fibword_phi(int n);

int main(){
    int i=1;
    while(fibword_subs(i)==fibword_phi(i) && i<MAXSIZE){
        i++;
    }
    if (i>=MAXSIZE){
        printf("the loop could not find a wrong digit within the max size\n");
    }
    printf("the %dth digit went wrong\n",i);
}


bool fibword_subs(int n){
    if(n<0){
        printf("wrong input, the function will return a 0.");
        return false;
    }
    int arr[MAXSIZE]={0};
    int i=0;
    int count=1;
    
    while(count<n){
        if(arr[i]==0){
            arr[count]=1;
            count+=2;
            i++;
        }else{
            count++;
            i++;
        }
    }
    return (bool)arr[n-1];
}

bool fibword_phi(int n){
    int temp=2+floor(n*PHI)-floor((n+1)*PHI);
    return (bool)temp;
}
