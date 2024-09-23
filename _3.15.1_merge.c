#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h> //only used in test function

int overlap(const char s1[],const char s2[]);
void substring(const char s[],int index1, int index2, char out[]);
void test();

int main(){

    test();
    
    printf("%d\n",overlap("abcde","cdefg"));
    
    return 0;
}

int overlap(const char s1[],const char s2[]){
    int len1=strlen(s1);
    int len2=strlen(s2);
    int min=len1<len2?len1:len2;
    char temp1[100];
    char temp2[100];
    
    for(int i=0;i<min;i++){
        substring(s1,min-len1+i,len1-1,temp1);
        int k;
        k=0;
        while(temp1[k]!='\0'){
            printf("%c ",temp1[k]);
            k++;
        }
        printf("\n");
        substring(s2,0,min-i-1,temp2);
        k=0;
        while(temp2[k]!='\0'){
            printf("%c ",temp2[k]);
            k++;
        }
        printf("\n");
        if(!strcmp(temp1,temp2)){
            return i;
        }
        int j;
        for(j=0;j<100;j++){
            temp1[j]=0;
        }
        for(j=0;j<100;j++){
            temp2[j]=0;
        }
    }
    return -1;
}

void substring(const char s[],int index1, int index2, char out[]){
    int i;
    for(i=0;i<=index2-index1;i++){
        out[i]=s[i+index1];
    }
    out[i+1]='\0';
}


void test(){
    assert(strlen("abc")==3);
    
    char temp[100];
    
    int i=0;
    
    for(i=0;i<100;i++){
        temp[i]=0;
    }
    substring("abcd",0,2,temp);
    assert(strcmp(temp,"abc")==false);
    
    for(i=0;i<100;i++){
        temp[i]=0;
    }
    substring("abcd",1,2,temp);
    assert(strcmp(temp,"bc")==false);
    
    
    for(i=0;i<100;i++){
        temp[i]=0;
    }
    substring("abcd",1,1,temp);
    assert(strcmp(temp,"b")==false);

    for(i=0;i<100;i++){
        temp[i]=0;
    }
    substring("abcd",2,3,temp);
    assert(strcmp(temp,"cd")==false);

}
