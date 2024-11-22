#include "t27.h"

#define BUFFERSIZE 200

/*
struct dict {
   struct dict* dwn[ALPHA];
   struct dict* up; 
   bool terminal;
   int freq;
};
*/
// 'Internal' function prototypes 
// ...
bool __isvalid(const char* wd);
int __char2num(char c);
void __freenodes(dict* p);
void __countfreq(const dict* p, int* count);
void __countnode(const dict* p, int* count);
dict* __findword(dict* p, const char* str);
void __findmostcommon(dict* p, int* mc);
int __compare(char* s1, char* s2);
char* __node2str(dict* p);
void __findautocomplete(dict* p, int* mc, dict** dest);

dict* dict_init(void){
    dict* root=calloc(1,sizeof(dict));
    if(!root){
        return NULL;
    }
    return root;
}

bool __isvalid(const char* wd){
    if(!wd){
        return false;
    }
    int i=0;
    while(wd[i]){
        bool valid = isalpha(wd[i]) || wd[i]=='\'';
        if(!valid){
            return false;
        }
        i++;
    }
    return true;
}

int __char2num(char c){
    if('a'<=c && c<='z'){
        return c-'a';
    }else if('A'<=c && c<='Z'){
        return c-'A';
    }else if(c=='\''){
        return ALPHA-1;
    }
    return -1;
}

bool dict_addword(dict* p, const char* wd){
    if(!p || !wd){
        return false;
    }
    if(!__isvalid(wd)){
        return false;
    }
    int i=0;
    while(wd[i]){
        int next=__char2num(wd[i]);
        if(!p->dwn[next]){
            p->dwn[next]=dict_init();
            if(!p->dwn[next]){
                return false;
            }
            p->dwn[next]->up=p;
        }
        p=p->dwn[next];
        i++;
    }
    p->terminal=true;
    (p->freq)++;
    return true;
}

void __freenodes(dict* p){
    if(!p){
        return;
    }
    for(int i=0;i<ALPHA;i++){
        __freenodes(p->dwn[i]);
    }
    free(p);
}

void dict_free(dict** p){
    if(!p || !(*p)){
        return;
    }
    __freenodes(*p);
    *p=NULL;
}

void __countfreq(const dict* p, int* count){
    if(!p){
        return;
    }
    for(int i=0;i<ALPHA;i++){
        __countfreq(p->dwn[i],count);
    }
    if(p->terminal){
        (*count)+=p->freq;
    }
}

int dict_wordcount(const dict* p){
    if(!p){
        return 0;
    }
    int count=0;
    __countfreq(p,&count);
    return count;
}

void __countnode(const dict* p, int* count){
    if(!p){
        return;
    }
    (*count)++;
    for(int i=0;i<ALPHA;i++){
        __countfreq(p->dwn[i],count);
    }
}

int dict_nodecount(const dict* p){
    if(!p){
        return 0;
    }
    int count=0;
    __countnode(p,&count);
    return count;
}


dict* __findword(dict* p, const char* str){
    if(!p || !str){
        return NULL;
    }
    if(*str=='\0'){
        if(p->terminal){
            return p;
        }else{
            return NULL;
        }
    }
    int next = __char2num(*str);
    if(!p->dwn[next]){
        return NULL;
    }
    return __findword(p->dwn[next],str+1);
}

dict* dict_spell(const dict* p, const char* str){
    if(!p || !str){
        return NULL;
    }
    if(!__isvalid(str)){
        return NULL;
    }
    dict* d=p;
    return __findword(d,str);
}

void __findmostcommon(dict* p, int* mc){
    if(!p){
        return;
    }
    if(p->terminal){
        *mc=*mc<p->freq?p->freq:*mc;
    }
    for(int i=0;i<ALPHA;i++){
        __findmostcommon(p->dwn[i],mc);
    }
}

int dict_mostcommon(const dict* p){
    if(!p){
        return 0;
    }
    int mc=0;
    dict* d=p;
    __findmostcommon(d,&mc);
    return mc;
}

// CHALLENGE1
unsigned dict_cmp(dict* p1, dict* p2){
    if(!p1 || !p2){
        exit(1);
    }
    dict* buffer[BUFFERSIZE];
    unsigned n=0;
    while(!p1){
        buffer[n]=p1;
        p1=p1->up;
        n++;
    }
    bool flag=false;
    unsigned i=0;
    while(!p2 && !flag){
        i=0;
        for(;i<n && !flag;i++){
            if(buffer[i]==p2){
                flag=true;
            }
        }
        p2=p2->up;
    }
    return n+i-1;
}

// return 1: s1<s2 0: s1=s2 -1: s1>s2
int __compare(char* s1, char* s2){
    int len1=!s1?0:strlen(s1);
    int len2=!s2?0:strlen(s2);
    if(len1!=len2){
        return len2-len1;
    }
    int i=0;
    while(i<len1){
        if(s1[i]!=s2[i]){
            return s2[i]-s1[i];
        }
        i++;
    }
    return 0;
}

char* __node2str(dict* p){
    char buffer[BUFFERSIZE]={0};
    char* b=buffer;
    while(p){
        dict* temp=p;
        p=p->up;
        bool flag=false;
        int i=0;
        for(;i<ALPHA && !flag;i++){
            if(p->dwn[i]==temp){
                flag=true;
            }
        }
        if(!flag){
            exit(1);
        }
        if(i==ALPHA){
            *b='\'';
        }else{
            *b=(--i)+'a';
        }
        b++;
    }
    int len=strlen(buffer);
    char* str=calloc(1+len,sizeof(char));
    for(int i=0;i<len;i++){
        str[i]=buffer[len-i-1];
    }
    return str;
}

void __findautocomplete(dict* p, int* mc, dict** dest){
    if(!p){
        return;
    }
    if(p->terminal){
        if(p->freq>*mc){
            *mc=p->freq;
            *dest=p;
        }else if(p->freq==*mc){
            char* s1=__node2str(p);
            char* s2=__node2str(dest);
            if(__compare(s1,s2)>0){
                *dest=p;
            }
            free(s1);
            free(s2);
        }
    }
    for(int i=0;i<ALPHA;i++){
        __findautocomplete(p->dwn[i],mc,dest);
    }
}

// CHALLENGE2
void dict_autocomplete(const dict* p, const char* wd, char* ret){
    if(!p || !wd){
        if(!ret){
            return;
        }else{
            ret[0]=0;
            return;
        }
    }
    if(!__isvalid(wd)){
        ret[0]=0;
        return;
    }
    int mc=0;
    dict* dest=NULL;
    __findautocomplete(p,&mc,&dest);
    if(!dest){
        ret[0]=0;
        return;
    }
    char* str=__node2str(dest);
    int i=0;
    bool flag=false;
    while(wd[i] && !flag){
        if(wd[i]!=str[i]){
            flag=true;
        }
        i++;
    }
    strcpy(ret,str+i-1);
}

void test(void){
    
}
