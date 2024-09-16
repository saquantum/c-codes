#include<stdio.h>
#include<ctype.h>

#define DIFF 'a'-'A'

typedef enum bool{False,True} bool;
bool isvowel(char c);

int main(){
    char c;
    while((c=getchar())!=EOF){
        if (isvowel(c)){
            putchar(toupper((int)c));
        }else{
            putchar(tolower((int)c));
        }
    }
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
