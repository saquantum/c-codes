// cat words_alpha.txt | grep -E ^[a-zA-Z]{4}$ >> four.txt

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

#define MAXSIZE 50
#define FILEPATH "words_alpha.txt"

int numberOfUncommon(char* dest, char* source);
int* arrayOfUncommon(char* dest, char* source);
void swap(int* a, int* b);
void permute(int* arr, int s, int e, char* dest, char* source);
bool findWords(char* str);
bool isValid(int* permutation, char* dest, char* source);
void test();

int main(int argc, char** argv) {
    assert(argc==3);
    assert(strlen(argv[1])==strlen(argv[2]));
    test();
    int* arr=arrayOfUncommon(argv[1],argv[2]);
    permute(arr,0,numberOfUncommon(argv[1],argv[2])-1,argv[1],argv[2]);
    free(arr);
}

int numberOfUncommon(char* dest, char* source){
    assert(strlen(dest)==strlen(source));
    int len=strlen(dest);
    int uncommon=0;
    
    for(int i=0;i<len;i++){
        if(dest[i]!=source[i]){
            uncommon++;
        }   
    }
    return uncommon;
}

int* arrayOfUncommon(char* dest, char* source){
    assert(strlen(dest)==strlen(source));
    int uncommon=numberOfUncommon(dest,source);
    int len=strlen(dest);
    int k=0;
    int* arr=(int*)calloc(uncommon,sizeof(int));
    for(int i=0;i<len;i++){
        if(dest[i]!=source[i]){
            arr[k]=i;
            k++;
        }
    }
    return arr;
}

void swap(int* a, int* b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void permute(int* arr, int s, int e, char* dest, char* source){
    if(s==e){
        if(isValid(arr,dest,source)){
            for(int i=0;i<numberOfUncommon(dest,source);i++){
                printf("%d ",arr[i]);
            }
            printf("\n");
        }
    }
    for(int i=s;i<=e;i++){
        swap(arr+s,arr+i);
        permute(arr,s+1,e,dest,source);
        swap(arr+s,arr+i);
    }
}

bool isValid(int* permutation, char* dest, char* source){
    int len=numberOfUncommon(dest,source);
    char buffer[MAXSIZE]={0};
    // a permutation is a length 4 int array.{2,1,0,3}
    for(int i=0;i<len;i++){
        strcpy(buffer,source);
        for(int j=0;j<=i;j++){
            buffer[permutation[j]]=dest[permutation[j]];
        }
        if(!findWords(buffer)){
            return false;
        }
    }
    return true;
}

bool findWords(char* str){
    FILE* fp=fopen(FILEPATH,"r");
    char buffer[MAXSIZE]={0};
    while(fgets(buffer,MAXSIZE,fp)){
        for(int i=0;i<MAXSIZE;i++){
            if(buffer[i]=='\n'){
                buffer[i]='\0';
            }
        }
        if(!strcmp(buffer,str)){
            fclose(fp);
            return true;
        } 
    }
    fclose(fp);
    return false;
}

void test(){
    assert(findWords("drag"));
    //assert(!findWords("sit"));
    int perm1[4]={2,1,0,3};
    assert(isValid(perm1,"warm","cold"));
    int perm2[4]={2,3,0,1};
    assert(isValid(perm2,"mall","poke"));
    int perm3[4]={3,0,2,1};
    assert(isValid(perm3,"tons","cube"));
}
