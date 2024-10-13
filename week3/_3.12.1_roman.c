#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdbool.h>

int roman3999(const char s[]);
int roman2arab(char c);
void test();

int main(){
    test();
    printf("%d %d %d\n",roman3999("MCMXCIX"),roman3999("MCMLXVII"),roman3999("MCDXCI"));
}

int roman3999(const char s[]){
    
    int i=0;
    int len=strlen(s);
    int sum=0;
    
    while(i<len){
        if(i==len-1 || roman2arab(s[i])>=roman2arab(s[i+1])){
            sum+=roman2arab(s[i]);
            i++;
        }else{
            sum=sum-roman2arab(s[i])+roman2arab(s[i+1]);
            i+=2;
        }
    }
    return sum;
}

int roman2arab(char c){
    char table[7]={'I','V','X','L','C','D','M'};
    int value[7]={1,5,10,50,100,500,1000};

    for(int i=0;i<7;i++){ // 7 is the length of table 
        if (c==table[i]){
            return value[i]; 
        }
    }
    printf("wrong converting, will output -1 as a result\n");
    return -1;
}

void test(){
    assert(roman2arab('I')==1);
    assert(roman2arab('V')==5);
    assert(roman2arab('X')==10);
    assert(roman2arab('L')==50);
    assert(roman2arab('C')==100);
    assert(roman2arab('D')==500);
    assert(roman2arab('M')==1000);
    assert(roman3999("IV")==4);
    assert(roman3999("IX")==9);
    assert(roman3999("XL")==40);
    assert(roman3999("XC")==90);
    assert(roman3999("CD")==400);
    assert(roman3999("CM")==900);
    assert(roman3999("MC")==1100);
    
    assert(roman3999("MCMXCIX")==1999);
    assert(roman3999("MCMLXVII")==1967);
    assert(roman3999("MCDXCI")==1491);
}
