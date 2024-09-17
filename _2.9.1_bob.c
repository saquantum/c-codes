#include<stdio.h>
#include<ctype.h>
#include<assert.h>

typedef enum bool{False,True} bool;
bool isvowel(char c);
bool is_prime(int n);
void test();

int main(){
    test();
    int count=0;
    char a1;
    char a2;
    char a3;
    
    for (char c1='a';c1<='z';c1++){
        a1=c1;
        a3=a1;
        for (char c2='a';c2<='z';c2++){
            /* Use xor to determine whether the first and second characters are different.
            To determine whether we get a prime, first set 'a' to be 1 using 'a'-('a'-1) 
            and the same procedure applies to other characters.*/
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

void test(){
    assert(isvowel('a')==1);
    assert(isvowel('E')==1);
    assert(isvowel('1')==0);
    assert(isvowel('0')==0);
    assert(isvowel('x')==0);
    assert(isvowel('R')==0);
    assert(isvowel('\n')==0);
    assert(isvowel('\0')==0);

    assert(is_prime(2)==1);
    assert(is_prime(3)==1);
    assert(is_prime(4)==0);
    assert(is_prime(5)==1);
    assert(is_prime(6)==0);
    assert(is_prime(7)==1);
    assert(is_prime(8)==0);
    assert(is_prime(9)==0);
    assert(is_prime(10)==0);
    assert(is_prime(11)==1);
    assert(is_prime(13)==1);
    assert(is_prime(15)==0);
    assert(is_prime(17)==1);
    assert(is_prime(29)==1);
    assert(is_prime(57)==0);
    assert(is_prime(1987)==1);
}


