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
int find_anagrams(char* out, char* var, char* dict_path);

int main(){

    test();
    
    
    FILE* words=fopen("words.txt","r");
    assert(words);
    char lines[MAXSIZE]={0};
    while((fgets(lines,sizeof(lines),words))){
        lines[strlen(lines)-1]='\0';
        char out[MAXSIZE]={0};
        int count=find_anagrams(out,lines,"words_alpha.txt");
        if (strlen(out) > 0) {
            printf("%d %s\n", count, out);
        }
    }
    fclose(words);
}

int find_anagrams(char* out, char* var, char* dict_path){
    int count=0;
    char lines[MAXSIZE]={0};
    FILE* fp=fopen(dict_path,"r");
    while((fgets(lines,sizeof(lines),fp))){
        lines[strlen(lines)-1]='\0';
        if (anagram(var,lines)){
            count++;
            snprintf(out+strlen(out),MAXSIZE-strlen(out),"%s ",lines);
        }
    }
    fclose(fp);
    return count;
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
