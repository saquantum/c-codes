#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h> //only used in test function

bool isletter(char c);
int leaveletters(char s[], char target[]);
bool ispalindrome(char s[]);
void test();

int main(){
    test();
    return 0;
}

int leaveletters(char s[], char target[]){
    int i=0;
    int count=0;
    int fuse=1000; // this is to prevent the while infinitely loops
    while(s[i]!='\0' || i>fuse){
        if (isletter(s[i])){
            target[count]=s[i];
            count++;
        }
        i++;
    }
    if (i<fuse){
        target[count]='\0';
        count++;
    }
    return count;
}

bool ispalindrome(char s[]){
    char t[100]={0}; // the max input length is 100
    int length=leaveletters(s, t);
    for(int i=0;i<length-1;i++){
        if( tolower((int) t[length-2-i]) != tolower((int) t[i]) ){
            return false;
        }
    }
    return true;
}

bool isletter(char c){
    if ('a'<=c && c<='z'){
        return true;
    }else if('A'<=c && c<='Z'){
        return true;
    }
    return false;
}

void test(){
    
    char temp[200];
    int n=leaveletters("a, b! c",temp);
    assert(strcmp("abc",temp)==false);
    assert(n==4);
    
    assert(ispalindrome("a,!")==true);
    assert(ispalindrome("a, a!")==true);
    assert(ispalindrome("a, b! cb && a")==true);
    assert(ispalindrome("kayak")==true);
    assert(ispalindrome("AbcBa")==true);
    assert(ispalindrome("A man, a plan, a canal: Panama!")==true);
    assert(ispalindrome("Madam, in Eden I'm Adam")==true);
    assert(ispalindrome("Level, madam, level!")==true);
    assert(ispalindrome("A B C D A")==false);
}
