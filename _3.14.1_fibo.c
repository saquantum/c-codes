#include<stdio.h> 
#include<assert.h> 
#include<math.h>
#include<stdbool.h>
#include<string.h>

#define PHI 1.61803
#define MAXSIZE 10000

bool fibword_subs(int n);
bool fibword_phi(int n);
bool fibword_str(int n);

int main(){
    int i=1;
    while(fibword_str(i)==fibword_phi(i)){
        i++;
    }
    printf("the %dth digit went wrong\n",i);
}

bool fibword_str(int n){
    
    char s[MAXSIZE];
    s[0]='0';
    int len=1;
    s[len]='\0';
    int pos=0;
    
    while(len<n){
        if(s[pos]=='0'){
            strcat(s,"10");
            len+=2;
            pos++;
        }else{
            strcat(s,"0");
            len+=1;
            pos++;
        }
    }
    return s[n];
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
