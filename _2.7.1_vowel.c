#include<stdio.h>
#include<ctype.h>
#include<assert.h>

typedef enum bool{False,True} bool;
bool isvowel(char c);
void test();

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

void test(){
    assert(isvowel('a')==1);
    assert(isvowel('E')==1);
    assert(isvowel('1')==0);
    assert(isvowel('0')==0);
    assert(isvowel('x')==0);
    assert(isvowel('R')==0);
    assert(isvowel('\n')==0);
    assert(isvowel('\0')==0);
}
