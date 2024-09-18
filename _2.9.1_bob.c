#include<stdio.h>
#include<ctype.h>
#include<assert.h>
#include<math.h>

typedef enum bool{False,True} bool;

bool isvowel(char c);
bool isprime(int n);
int let2num(char a);
void test();

int main(){
    test();
    int count=0;
    
    for (char c1='a';c1<='z';c1++){

        for (char c2='a';c2<='z';c2++){
            /* 
               Use xor to determine whether the first and second characters are different.
            */
            if( (isvowel(c1)^isvowel(c2))==True \
            && isprime(let2num(c1)+let2num(c2)+let2num(c1)) ){
                count++;
                printf("%d %c%c%c ",count,c1,c2,c1);
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

bool isprime(int n){
    if (n<=2){
        return True;
    }
    for(int i=2;i<=floor(sqrt((double)n));i++){
        if (n%i==0){
            return False;
        }
    }
    return True;
}

int let2num(char a){
    /* change lower case letters into number 
       by the rule: 'a'->1, 'b'->2, ... 
    */  
    if (!(a>='a' && a<='z')){
        return (int)a;
    }
    return a-'a'+1;
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

    assert(isprime(2)==1);
    assert(isprime(3)==1);
    assert(isprime(4)==0);
    assert(isprime(5)==1);
    assert(isprime(6)==0);
    assert(isprime(7)==1);
    assert(isprime(8)==0);
    assert(isprime(9)==0);
    assert(isprime(10)==0);
    assert(isprime(11)==1);
    assert(isprime(13)==1);
    assert(isprime(15)==0);
    assert(isprime(17)==1);
    assert(isprime(29)==1);
    assert(isprime(57)==0);
    assert(isprime(1987)==1);

    assert(let2num('a')==1);
    assert(let2num('b')==2);
    assert(let2num('c')==3);
    assert(let2num('x')==24);
    assert(let2num('y')==25);
    assert(let2num('z')==26);
    assert(let2num('\n')==(int)'\n');
    assert(let2num('A')==(int)'A');
    assert(let2num('6')==(int)'6');
    assert(let2num('\\')=='\\');
}
