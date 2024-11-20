#include "bst.h"

bst* bst_init(){
    bst* b=malloc(sizeof(bst));
    if(!b){
        return NULL;
    }
    b->root=NULL;
    b->size=0;
    b->datatype=NULL;
    return b;
}

node* bst_get(bst* b, char* datatype, void* data){
    if(!b || !datatype || !data){
        return NULL;
    }
    if(!b->datatype || strcmp(b->datatype,datatype)){
        return NULL;
    }
    return __get(b->root, datatype, data);
}

node* __get(node* n, char* datatype, void* data){
    if(!n || !datatype || !data){
        return NULL;
    }
    int cmp=__compare(datatype, data, n->data);
    if(cmp>0){ // data < n->data, go to left child 
        return __get(n->left, datatype, data);
    }else if(cmp<0){ 
        return __get(n->right, datatype, data);
    }else{
        return n;
    }
}

// returns 1 if data1 < data2.
int __compare(char* datatype, void* data1, void* data2) {
    if (strcmp(datatype, "int") == 0) {
        int d1 = *(int*)data1, d2 = *(int*)data2;
        return (d1 < d2) ? 1 : (d1 > d2) ? -1 : 0;
    } else if (strcmp(datatype, "char") == 0) {
        char d1 = *(char*)data1, d2 = *(char*)data2;
        return (d1 < d2) ? 1 : (d1 > d2) ? -1 : 0;
    } else if (strcmp(datatype, "short") == 0) {
        short d1 = *(short*)data1, d2 = *(short*)data2;
        return (d1 < d2) ? 1 : (d1 > d2) ? -1 : 0;
    } else if (strcmp(datatype, "long") == 0) {
        long d1 = *(long*)data1, d2 = *(long*)data2;
        return (d1 < d2) ? 1 : (d1 > d2) ? -1 : 0;
    } else if (strcmp(datatype, "double") == 0) {
        double d1 = *(double*)data1, d2 = *(double*)data2;
        return (d1 < d2) ? 1 : (d1 > d2) ? -1 : 0;
    } else if (strcmp(datatype, "float") == 0) {
        float d1 = *(float*)data1, d2 = *(float*)data2;
        return (d1 < d2) ? 1 : (d1 > d2) ? -1 : 0;
    } else {
        printf("Unsupported datatype: %s\n", datatype);
        exit(1);
    }
}

bool bst_insert(bst* b, char* datatype, void* data){
    if(!b || !datatype || !data){
        return false;
    }
    if(!b->datatype){
        b->datatype=calloc(strlen(datatype)+1,sizeof(char));
        if(!b->datatype){
            return false;
        }
        strcpy(b->datatype,datatype);
    }
    if(strcmp(datatype,b->datatype)){
        printf("Inserting inconsistent datatype, failed.\n");
        return false;
    }
    
    b->root=__insert(b->root, b->datatype, data);
    if(b->root){
        b->size++;
        return true;
    }
    return false;
}

node* __insert(node* n, char* datatype, void* data){
    // exit condition: reached null child
    if(!n){
        return __makenode(datatype,data);
    }
    if(!datatype){
        exit(1);
    }
    
    int cmp = __compare(datatype, data, n->data);   
    if(cmp>0){ // data < n->data
        n->left=__insert(n->left,datatype,data);
    }else if(cmp<0){
        n->right=__insert(n->right,datatype,data);
    }
    // this node already exists, do nothing.
    return n;
}

node* __makenode(char* datatype, void* data){
    if(!datatype || !data){
        return NULL;
    }
    node* n = (node*)calloc(1,sizeof(node));
    if(!n){
        return NULL;
    }
    int datasize = __getsize(datatype);
    if(datasize!=-1){
        n->data=malloc(datasize);
        if (!n->data) {
            free(n);
            return NULL;
        }
    }
    if (strcmp(datatype, "int") == 0) {
        *(int*)n->data = *(int*)data;
    }else if (strcmp(datatype, "char") == 0) {
        *(char*)n->data = *(char*)data;
    }else if (strcmp(datatype, "short") == 0) {
        *(short*)n->data = *(short*)data;
    }else if (strcmp(datatype, "long") == 0) {
        *(long*)n->data = *(long*)data;
    }else if (strcmp(datatype, "double") == 0) {
        *(double*)n->data = *(double*)data;
    }else if (strcmp(datatype, "float") == 0) {
        *(float*)n->data = *(float*)data;
    }else {
        printf("Unsupported datatype: %s\n", datatype);
        return NULL;
    }
    return n;
}

bool bst_deletemin(bst* b){
    if(!b || !b->root){
        return false;
    }
    b->root = __deletemin(b->root);
    if(b->size>0){
        b->size--;
    }
    return true;
}

node* __deletemin(node* n){
    if(!n){
        return NULL;
    }
    // exit condition: found the minimum
    if(!n->left){
        node* temp=n->right;
        free(n->data);
        free(n);
        return temp;
    }
    
    n->left=__deletemin(n->left);
    return n;
}

bool bst_delete(bst* b, char* datatype, void* data){
    if(!b || !datatype || !data){
        return false;
    }
    if(strcmp(b->datatype, datatype)){
        return false;
    }
    b->root = __delete(b->root, datatype, data);
    if(b->size>0){
        b->size--;
    }
    return true;
}

node* __delete(node* n, char* datatype, void* data){
    // target node does not exist:
    if(!n){
        return NULL;
    }
    // keep looking for the target node
    int cmp = __compare(datatype, data, n->data);   
    if(cmp>0){ // data < n->data
        n->left=__delete(n->left,datatype,data);
    }else if(cmp<0){
        n->right=__delete(n->right,datatype,data);
    }
    // once we've found the target node:
    else{
        // if only one side of it has a subtree, it's easy:
        if(!n->right){
            node* temp = n->left;
            free(n->data);
            free(n);
            return temp;
        }
        if(!n->left){
            node* temp = n->right;
            free(n->data);
            free(n);
            return temp;
        }
        // if both sides are occupied:
        // find the minimum of its right subtree, and replace n by this entry, 
        // and concatenate minimum's right subtree to its parent
        node* min = __min(n->right);
        int datasize = __getsize(datatype);
        if(datasize==-1){
            exit(1);
        }
        memcpy(n->data, min->data, datasize);
        n->right = __deletemin(n->right); // delete min to concatenate and preserve BST structure
    }
    return n;
}

node* __min(node* n) {
    while (n && n->left) {
        n = n->left;
    }
    return n;
}

int __getsize(char* datatype){
    if(!datatype){
        return -1;
    }
    if(!strcmp(datatype, "int")){
        return sizeof(int);
    }else if(!strcmp(datatype, "char")){
        return sizeof(char);
    }else if(!strcmp(datatype, "short")){
        return sizeof(short);
    }else if(!strcmp(datatype, "long")){
        return sizeof(long);
    }else if(!strcmp(datatype, "float")){
        return sizeof(float);
    }else if(!strcmp(datatype, "double")){
        return sizeof(double);
    }else{
        printf("Unsupported datatype: %s\n", datatype);
        exit(1);
    }
}

void printBST(bst* b, void (*style)(char***,int)){
    // put bst into arrays and calculate depth
    int depth=1;
    char*** str = __bst2strings(b, &depth, b->datatype);
    if(!str){
        return;
    }
    style(str, depth);
    
    for(int j=0;j<depth+1;j++){
        for(int i=0;i<(1<<j);i++){
            free(str[j][i]);
        }
        free(str[j]);
    }
    free(str);
}

void __treestyle(char*** strings, int depth){
    if(!strings){
        return;
    }
    //build the flattened tree first    
    int inserted=(1<<depth)-1;
    int* tempx=calloc(inserted, sizeof(int));
    int* tempy=calloc(inserted, sizeof(int));
    memset(tempy,-1,inserted*sizeof(int));
    for(int j=1;j<=depth;j++){
        int k=0;
        for(;k<inserted && tempy[k]!=-1;k++);
        int index=0;
        for(int i=k;i<inserted;i+=(1<<j)){
            tempy[i]=depth-j-1;
            tempx[i]=index++;
        }
    }
    int total=(1<<depth)-1;
    int* ftx=calloc(total,sizeof(int));
    int* fty=calloc(total,sizeof(int));
    for(int i=0;i<total;i++){
        if(i%2==0){
            ftx[i]=i/2;
            fty[i]=depth-1;
        }else{
            ftx[i]=tempx[i/2];
            fty[i]=tempy[i/2];
        }
    }
    free(tempx);
    free(tempy);

    char spaces[BUFFERSIZE]={0};
    for(int row=0;row<depth+1;row++){
        int spacelen=0;
        for(int i=0;i<total;i++){
            if(fty[i]!=row){
                spacelen+=strlen(strings[fty[i]][ftx[i]]);
            }else{
                spaces[0]=0;
                __printspaces(spaces,spacelen);
                spacelen=0;
                printf("%s",spaces);
                printf("%s",strings[fty[i]][ftx[i]]);
            }
        }
        printf("\n");
    }
    free(ftx);
    free(fty);
}

// given new coordinate (x,y), return old coordinate
bool __entry(int* x, int* y, int rows) {
    if (!x || !y) {
        return false;
    }
    if(*y<0 || *y>=rows){ 
        return false;
    }
    if(*x<0 || *x>=(1<<(*y+1))-1){
        return false;
    }
    if((*x)%2==0) {
        *x=(*x)/2;
        return true;
    }
    
    // odd case:
    int inserted=(1<<(*y))-1;
    int* tempx=calloc(inserted, sizeof(int));
    int* tempy=calloc(inserted, sizeof(int));
    memset(tempy,-1,inserted*sizeof(int));
    for(int j=1;j<=*y;j++){
        int k=0;
        for(;k<inserted && tempy[k]!=-1;k++);
        int index=0;
        for(int i=k;i<inserted;i+=(1<<j)){
            tempy[i]=(*y)-j;
            tempx[i]=index++;
        }
    }
    
    *y=tempy[(*x)/2];
    *x=tempx[(*x)/2];
    free(tempx);
    free(tempy);
    return true; 
}

bool __printspaces(char* str, int n){
    if(!str || n<0){
        return false;
    }
    for(int i=0;i<n;i++){
        strcat(str," ");
    }
    return true;
}

void __arraystyle(char*** strings, int depth){
    if(!strings){
        return;
    }
    for(int j=0;j<depth;j++){
        for(int i=0;i<(1<<j);i++){
            if(!strcmp(strings[j][i],EMPTY)){
                printf("- ");
            }else{
                printf("%s ",strings[j][i]);
            }
        }
        printf("\n");
    }
}

char*** __bst2strings(bst* b, int* depth, char* datatype){
    if(!b || !depth || !datatype){
        return NULL;
    }
    // first calculate depth and make arrays of node
    node*** levels=calloc(*depth+1,sizeof(node**));
    for(int j=0;j<*depth+1;j++){
        levels[j]=calloc(1<<j,sizeof(node*));
    }
    levels[0][0]=b->root;
    for(int j=0;j<*depth;j++){
        bool flag=false;
        for(int i=0;i<(1<<j);i++){
            node* n=levels[j][i];
            if(n){
                levels[j+1][2*i]=n->left;
                levels[j+1][2*i+1]=n->right;
                flag=true;
            }
        }
        if(flag){
            (*depth)++;
            levels=realloc(levels, (*depth+1)*sizeof(node**));
            levels[*depth]=calloc(1<<*depth,sizeof(node*));
        }else{
            free(levels[(*depth)--]);
        }
    }
    
    // convert data to string
    char buffer[BUFFERSIZE];
    char*** strings=calloc(*depth+1,sizeof(char**));
    for(int j=0;j<*depth+1;j++){
        strings[j]=calloc(1<<j,sizeof(char*));
    }
    for(int j=0;j<*depth;j++){
        buffer[0]=0;
        for(int i=0;i<(1<<j);i++){
            node* n=levels[j][i];
            if(n){
                if(!strcmp(datatype,"int")){
                    sprintf(buffer, "%d",*(int*)n->data);
                }else if(!strcmp(datatype,"char")){
                    sprintf(buffer, "%c",*(char*)n->data);
                }else if(!strcmp(datatype,"short")){
                    sprintf(buffer, "%d",*(short*)n->data);
                }else if(!strcmp(datatype,"long")){
                    sprintf(buffer, "%ld",*(long*)n->data);
                }else if(!strcmp(datatype,"double")){
                    sprintf(buffer, "%.2lf",*(double*)n->data);
                }else if(!strcmp(datatype,"float")){
                    sprintf(buffer, "%.2f",*(float*)n->data);
                }else{
                    printf("Unsupported datatype: %s\n", datatype);
                    exit(1);
                }
            }else{
                sprintf(buffer, EMPTY);
            }
            strings[j][i]=calloc(strlen(buffer)+1,sizeof(char));
            strcpy(strings[j][i],buffer);
        }
    }
    // we don't need levels any more
    for(int j=0;j<*depth+1;j++){
        free(levels[j]);
    }
    free(levels);
    
    return strings;
}

void bst_free(bst* b){
    if(!b){
        return;
    }
    __free(b->root);
    free(b->datatype);
    free(b);
}

void __free(node* n){
    // exit condition
    if(!n){
        return;
    }
    if(n->left){
        __free(n->left);
    }
    if(n->right){
        __free(n->right);
    }
    free(n->data);
    free(n);
}


