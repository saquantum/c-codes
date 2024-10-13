#include<stdio.h> 
#include<assert.h> 
#include<math.h>
#include<stdbool.h>
#include<string.h>

void rot(char str[]);
char rot13(char c);
char rot5(char c);
void test();

int main(){

    test();
    
    char temp[]="Erzrzore: fubeg shapgvbaf; ubhfr-fglyr ehyrf :-)";
    rot(temp);
    printf("%s\n",temp);
    return 0;
}

void rot(char s[]){
    int i=0;
    while(s[i]!='\0'){
        s[i]=rot13(s[i]);
        s[i]=rot5(s[i]);
        i++;
    }
}

char rot13(char c){
    int out=(int) c;
    if('a'<=c && c<='z'){
        out=c+13;
        if(out>'z'){
            //out='a'+(out-'z')-1;
            out=out-26;
            
        }
    }
    if('A'<=c && c<='Z'){
        out=c+13;
        if(out>'Z'){
            //out='A'+(out-'Z')-1;
            out=out-26;
        }
    }
    return (char)out;
}

char rot5(char c){
    char out=c;
    if ('0'<=c && c<='9'){
        out=c+5;
        if(out>'9'){
            out=out-10;
        }
    }
    return out;
}

void test(){
    assert(rot13('a')=='n');
    assert(rot13('n')=='a');
    assert(rot13('b')=='o');
    assert(rot13('o')=='b');
    assert(rot13('z')=='m');
    assert(rot13('m')=='z');
    
    assert(rot5('0')=='5');
    assert(rot5('5')=='0');
    assert(rot5('1')=='6');
    assert(rot5('6')=='1');
    
    char temp[100]="Hello, World!";
    rot(temp);
    assert(strcmp(temp,"Uryyb, Jbeyq!")==false);
    
    
}
