#include<stdio.h>
#include<assert.h>
int secret (int a);
void test();
int main(){
    test();
    char c;
    while((c=getchar())!=EOF){
        putchar((char)(secret(c)));
    }
    return 0;
}

int secret(int a){
    if ('a'<=a && a<='z'){
        double dist=(double)'a'+12.5-(double)a;
        return (int)a+(int)(2*dist);
    }else if('A'<=a && a<='Z'){
        double dist=(double)'A'+12.5-(double)a;
        return (int)a+(int)(2*dist);
    }
    return a;
    
}

void test(){
    assert(secret('\n')=='\n');
    assert(secret('1')=='1');
    assert(secret('9')=='9');
    assert(secret('a')=='z');
    assert(secret('A')=='Z');
    assert(secret('b')=='y');
    assert(secret('B')=='Y');
    assert(secret('z')=='a');
    assert(secret('X')=='C');
    
   
}
