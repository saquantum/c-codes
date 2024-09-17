#include<stdio.h>
#include<ctype.h>

#define DIFF 'a'-'A'

typedef enum bool{False,True} bool;
bool isvowel(char c);

int main(){
    int count=0;
    char a1;
    char a2;
    char a3;
    
    for (char c1='a';c1<='z';c1++){
        if(!isvowel(c1)){
            a1=c1;
            for (char c2='a';c2<='z';c2++){
                if(isvowel(c2)){
                    a2=c2;
                    for (char c3='a';c3<='z';c3++){
                        if(!isvowel(c3)){
                            a3=c3;
                            count++;
                            printf("%d %c%c%c ",count,a1,a2,a3);
                        }
                    }
                }
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