#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

#define MAXSIZE 1000

bool anagram(char* var, char* src);
void test();
bool arrcmp(int* a1, int size1, int* a2, int size2);

int main(int argc,char** argv){

    test();
    
    assert(argc==2);
    char* s=(char*)malloc(sizeof(char)*(strlen(argv[1])+1));
    strcpy(s,argv[1]);
    FILE* fp=fopen("words_alpha.txt","r");
    assert(fp);
    char lines[MAXSIZE]={0};
    while((fgets(lines,sizeof(lines),fp))){
        lines[strlen(lines) -  1] = '\0';
        if (anagram(s,lines) && strcmp(s,lines)){
            printf("%s\n",lines);
        }
    }
    fclose(fp);
    free(s);
}

bool anagram(char* var, char* src){
    if(strlen(var)!=strlen(src)){
        return false;
    }
    int temp_var[26]={0};
    int temp_src[26]={0};
    int i=0;
    while(var[i]){
        if(!isalpha(var[i])){
            return false;
        }
        temp_var[tolower(var[i])-'a']++;
        temp_src[tolower(src[i])-'a']++;
        i++;
    }
    return arrcmp(temp_var,26,temp_src,26);
}

bool arrcmp(int* a1, int size1, int* a2, int size2){
    if(size1!=size2){
        return false;
    }
    for(int i=0;i<size1;i++){
        if (a1[i]!=a2[i]){
            return false;
        }
    }
    return true;
}

void test(){
    assert(anagram("stop","tops"));
    assert(anagram("stop","pots"));
    assert(anagram("stop","opts"));
    assert(anagram("stop","post"));
    assert(!anagram("stop","zuni"));
}
