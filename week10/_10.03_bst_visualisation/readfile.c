// there are still some edge cases not dealt with .. :(
// hope your test data is easy enough.

#include "bst.h"

int main(int argc, char** argv){
    assert(argc==2);
    FILE* fp=fopen(argv[1],"r");
    if(!fp){
        printf("no such file exists\n");
        return 1;
    }
    int depth=0;
    char*** strings = file2strings(fp,&depth);
    fclose(fp);
    __compactstyle(strings,depth);
    for(int j=0;j<depth+1;j++){
        for(int i=0;i<(1<<j);i++){
            if(strings[j][i]){
                free(strings[j][i]);
            }
        }
        free(strings[j]);
    }
    free(strings);
}


char*** file2strings(FILE* fp, int* depth){
    // calculate depth
    int temp=0;
    char c;
    while((c=fgetc(fp))!=EOF){
        if(c=='('){
            temp++;
            *depth=*depth<temp?temp:*depth;
        }else if(c==')'){
            temp--;
        }
    }
    
    // reset pointer
    rewind(fp);
    
    // initialize strings
    char*** strings=calloc((*depth)+1, sizeof(char**));
    if(!strings){
        exit(1);
    }
    for(int j=0;j<=*depth;j++){
        strings[j] = calloc(1<<j, sizeof(char*));
        if(!strings[j]){
            exit(1);
        }
        for(int i=0;i<1<<(j);i++){
            strings[j][i] = calloc(1+(int)strlen(EMPTY), sizeof(char*));
            if(!strings[j][i]){
                exit(1);
            }
            strcpy(strings[j][i],EMPTY);
        }
    }
    
    // shadow array: record if a node is traversed already
    bool** traversed = calloc((*depth) + 1, sizeof(bool*));
    if (!traversed) {
        exit(1);
    }
    for (int j = 0; j <= *depth; j++) {
        traversed[j] = calloc(1 << j, sizeof(bool));
        if (!traversed[j]) {
            exit(1);
        }
    }
    
    //20(10(5(*)(*))(17(*)(*)))(30(21(*)(*))(*))
    // put everything into strings
    int x=0;
    int y=0;
    
    char buffer[BUFFERSIZE]={0};
    while((c=fgetc(fp))!=EOF){
        if(c=='('){
            if(__bound(*depth+1,x,y) && !traversed[y][x]){
                free(strings[y][x]);
                strings[y][x]=calloc(1+(int)strlen(buffer), sizeof(char));
                if(!strings[y][x]){
                    exit(1);
                }
                strcpy(strings[y][x],buffer);
                traversed[y][x]=true;
            }
            // reset buffer and move to left child
            buffer[0]=0;
            x*=2;
            y++;
            // move to right child if left child is traversed
            if(__bound(*depth+1,x,y) && traversed[y][x]){
                x++;
            }
        }else if(c==')'){
            // copy buffer to current cell and backtrack
            if(__bound(*depth+1,x,y) && !traversed[y][x]){
                free(strings[y][x]);
                strings[y][x]=calloc(1+(int)strlen(buffer), sizeof(char));
                if(!strings[y][x]){
                    exit(1);
                }
                strcpy(strings[y][x],buffer);
                traversed[y][x]=true;
            }
            x/=2;
            y--;
        }else if(c=='*'){
            if(__bound(*depth+1,x,y)){
                strcpy(buffer,EMPTY);
            }
        }else if(c!='\n'){
            int len=strlen(buffer);
            buffer[len]=c;
            buffer[len+1]=0;
        }  
    }
    
    // free shadow array
    for (int j = 0; j <= *depth; j++) {
        free(traversed[j]);
    }
    free(traversed);
    
    
    return strings;
}
