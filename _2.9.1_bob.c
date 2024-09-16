#include<stdio.h>
#include<ctype.h>

#define DIFF 'a'-'A'

typedef enum bool{False,True} bool;
bool isvowel(char c);
bool is_prime(int n);

int main(){
    int count=0;
    char a1;
    char a2;
    char a3;
    
    for (char c1='a';c1<='z';c1++){
        a1=c1;
        a3=a1;
        for (char c2='a';c2<='z';c2++){
            if((isvowel(a1)^isvowel(c2))==True && is_prime(2*c1+c2-3*'a'+3)){
                a2=c2;
                count++;
                printf("%d %c%c%c ",count,a1,a2,a3);
            }
        }
    }
    printf("\n");
    return 0;
}

bool isvowel(char c){
    if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u'){
        return True;
    }
    if (c=='A' || c=='E' || c=='I' || c=='O' || c=='U'){
        return True;
    }
    return False;
}

bool is_prime(int n){
    if (n<=2){
        return True;
    }
    for(int i=2;i<n;i++){
        if (n%i==0){
            return False;
        }
    }
    return True;
}


