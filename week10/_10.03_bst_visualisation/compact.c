#include "bst.h"

bool __bound(int depth, int x, int y){
    return !(y>=depth || y<0 || x>=(1<<y) || x<0);
}

bool __isempty(char*** strings, int x, int y){
    return !strcmp(strings[y][x],EMPTY);
}

// efficient depth: count left transitions from root 
int __efficient_depth(char*** strings, int depth, int x, int y){
    if(strings && __isempty(strings,x,y)){
        exit(1);
        //return -1;
    }
    if(!__bound(depth, x, y)){
        exit(1);
        //return -1;
    }
    int d=0;
    while(y>0){
        if(x%2==0){
            d++;
        }
        x/=2;
        y--;
    }
    return d;
}

void __relative_root(int depth, int* x, int* y){
    if(!__bound(depth, *x, *y)){
        return;
    }
    while((*x)%2==0 && (*y)>0){
        (*x)/=2;
        (*y)--;
    }
}

// only call this function for node without left child
// scope: from its relative root down to itself
int __critical_width(char*** strings, char** compact, int depth, int x, int y){
    if(!compact || !__bound(depth,x,y)){
        exit(1);
        //return -1;
    }
    int rx=x, ry=y;
    __relative_root(depth,&rx,&ry);
    
    int ed = __efficient_depth(strings,depth,x,y);
    int red = __efficient_depth(strings,depth,rx,ry);
    int cw=0;
    while(ed>=red){
        cw=cw>(int)strlen(compact[2*ed])?cw:(int)strlen(compact[2*ed]);
        ed--;
    }
    return cw;
}

// draw all vertically aligned nodes
void __printVerticalLine(bool** printed, char*** strings, char** compact, int depth, int x, int y){
    // check if it does not have left child
//printf("current node: (%d,%d)\n",x,y);
    bool bound=__bound(depth,2*x,y+1);
    if(bound){
        bool notempty=!__isempty(strings,2*x,y+1);
        if(notempty){
//printf("bypassed.\n");
            return;
        }
    }
//printf("check passed.\n");
    int cw=1+__critical_width(strings,compact,depth,x,y);
    int ed=__efficient_depth(strings,depth,x,y);

    // complete logic: if currently a left child, print and backtrack.
    // if currently a right child, print and break.
    bool flag=true;
    while(flag){
        if(x%2==0 && y>=0){
            strist(compact[2*ed],strings[y][x],cw);
            printed[y][x]=true;
            x/=2;
            y--;
            ed--;
            if(y>=0){
                strist(compact[2*ed+1],"|",cw);
            }
        }else if(x%2==1 && y>=0){
            strist_withhyphens(compact[2*ed],strings[y][x],cw);
            printed[y][x]=true;
            flag=false;
        }else{
            flag=false;
        }
    }
}

void __compactstyle_recursion(bool** printed, char*** strings, char** compact, int depth, int x, int y) {
    if (!__bound(depth, x, y)){
        return;
    }
    if (__isempty(strings, x, y)){
        return;
    }

    // Process left child first
    __compactstyle_recursion(printed, strings, compact, depth, 2 * x, y + 1);
    
    // current node
    __printVerticalLine(printed,strings,compact,depth,x,y);    
    
    // Process right child
    __compactstyle_recursion(printed, strings, compact, depth, 2 * x + 1, y + 1);

}

void __compactstyle(char*** strings, int depth){
    if(!strings){
        return;
    }
    /*
    // debug
    printf("depth=%d\n",depth);
    for (int j = 0; j <= depth; j++) {
        printf("Level %d: ", j);
        for (int i = 0; i < (1 << j); i++) {  // 1 << j = 2^j
            if (strings[j][i]) {
                printf("%s ", strcmp(strings[j][i], EMPTY) ? strings[j][i] : ".");
            }
        }
        printf("\n");
    }
    */
    // even strings to store nodes, odd strings to store connectors
    char** compact=calloc(2*depth+1,sizeof(char*));
    if(!compact){
        exit(1);
    }
    for(int i=0;i<2*depth+1;i++){
        compact[i]=calloc(BUFFERSIZE,sizeof(char));
        if(!compact[i]){
            exit(1);
        }
    }
    // a shadow array to record printed info
    bool** printed=calloc(depth+1,sizeof(bool*));
    if(!printed){
        exit(1);
    }
    for(int i=0;i<depth+1;i++){
        printed[i]=calloc(1<<(i+1),sizeof(bool));
        if(!printed[i]){
            exit(1);
        }
    }
    
    __compactstyle_recursion(printed,strings,compact,depth,0,0);
    
    // print and free:
    for(int i=0;i<depth+1;i++){
        free(printed[i]);
    }
    for(int i=0;i<2*depth+1;i++){
        if((int)strlen(compact[i])>0){
            printf("%s\n",compact[i]);
        }
        free(compact[i]);
    }
    printf("\n");
    free(compact);
    free(printed);
}


void __inorderstyle(char*** strings, int depth){
    __inorderTraversal_recursion(strings,depth,0,0);
    printf("\n");
}

void __inorderTraversal_recursion(char*** strings, int depth, int x, int y){
    // exit condition: out of bound, or null node
    if(!__bound(depth,x,y) || __isempty(strings,x,y)){
        return;
    }
    // left child:
    __inorderTraversal_recursion(strings, depth, 2*x,y+1);
    // current node:
    printf("%s ",strings[y][x]);
    // right child:
    __inorderTraversal_recursion(strings, depth, 2*x+1,y+1);
}

char* substring(const char* source, int s, int e){
    if(!source){
        return NULL;
    }
    if(e<s){
        return NULL;
    }
    if(e==s){
        return calloc(1,sizeof(char));
    }
    if(s<0 || e<0){
        return NULL;
    }
    char* str=calloc(e-s+1,sizeof(char));
    for(int i=s;i<e;i++){
        str[i-s]=source[i];
    }
    return str;
}

// string insertion
bool strist(char* dest, const char* src, int pos){
    if(!dest || !src){
        return false;
    }
    if(pos<0){
        return false;
    }
    if(pos>(int)strlen(dest)){
        while((int)strlen(dest)<pos){
            strcat(dest," ");
        }
        strcat(dest,src);
        return true;
    }
    char* s1 = substring(dest,0,pos);
    char* s2 = substring(dest,pos,strlen(dest)+1);
    dest[0]=0;
    if(s1){
        strcat(dest,s1);
        free(s1);
    }
    strcat(dest,src);
    if(s2){
        strcat(dest,s2);
        free(s2);
    }
    return true;
}

bool strist_withhyphens(char* dest, const char* src, int pos){
    if(!dest || !src){
        return false;
    }
    if(pos<0){
        return false;
    }
    if(pos>(int)strlen(dest)){
        while((int)strlen(dest)<pos){
            strcat(dest,"-");
        }
        strcat(dest,src);
        return true;
    }
    char* s1 = substring(dest,0,pos);
    char* s2 = substring(dest,pos,strlen(dest)+1);
    dest[0]=0;
    if(s1){
        strcat(dest,s1);
        free(s1);
    }
    strcat(dest,src);
    if(s2){
        strcat(dest,s2);
        free(s2);
    }
    return true;
}



