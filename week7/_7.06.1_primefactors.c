#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>

#define MAXSIZE 100
int parseint(char* str);
int* primefactors(int n);
bool isprime(int n);
void test();

int main(int argc, char** argv){
    assert(argc==2);
    int n=parseint(argv[1]);
    int* a=primefactors(n);
    free(a);
    test();
    
    
}

int parseint(char* str){
    int n=0;
    int i=0;
    while(str[i]){
        if(!('0'<=str[i] && str[i]<='9'))
        n=n*10+(str[i]-'0');
        i++;
    } 
    return n;
}

int* primefactors(int n){
    int buffer[MAXSIZE]={0};
    int count=0;
    while(n>1){
    bool flag=true;
        for(int i=2;flag && i<=n;i++){
            if(isprime(i) && n%i==0){
                buffer[count]=i;
                printf("%d ",i);
                count++;
                flag=false;
                n=n/i;
            }
        }
        if (flag) {  // If no prime divisor is found, n is prime
            buffer[count] = n;
            count++;
            n=1;
        }
    }
    int* a=(int*)malloc(count*sizeof(int));
    assert(a);
    for(int i=0;i<count;i++){
        a[i]=buffer[i];
    }
    return a;
}

bool isprime(int n){
    if (n<=1){
        return false;
    }
    if (n==2){
        return true;
    }
    if(n%2==0){
        return false;
    }
    for(int i=3;i<=floor(sqrt((double)n));i+=2){
        if (n%i==0){
            return false;
        }
    }
    return true;
}

void test(){
    assert(isprime(2));
    assert(isprime(3));
    assert(!isprime(4));
    assert(isprime(5));
    assert(!isprime(6));
    assert(isprime(7));
    assert(!isprime(8));
    assert(!isprime(9));
    
}
