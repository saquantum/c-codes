#include<stdio.h> 
#include<assert.h> 
#include<math.h>
#include<stdbool.h>

#define PHI 1.61803

bool fibword_subs(int n);
bool fibword_phi(int n);

int main(){
    int i=1;
    while(fibword_subs(i)==fibword_phi(i)){
        i++;
    }
    printf("the %dth digit went wrong\n",i);
}


bool fibword_subs(int n){
    if(n<0){
        printf("wrong input, the function will return a 0.");
        return false;
    }
    int length=n+4;
    int arr[length];
    int i;
    for(i=0;i<length;i++){
        arr[i]=0;
    }
    
    int count=1;
    i=0;
    
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
