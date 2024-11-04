#include "mydefs.h"

bool file2str(const char* fname, char* str){
    if(!fname || !str){
        return false;
    }
    FILE* fp=fopen(fname,"r");
    if(!fp){
        return false;
    }
    char* tempstr=(char*)calloc(MAXSTR+1,sizeof(char)); // here +1, to remove the final hyphen
    if(!copyfile2str(fp, tempstr)){
        free(tempstr);
        fclose(fp);
        return false;
    }
    fclose(fp);
    strcpy(str,tempstr);
    free(tempstr);
    return true;
}

bool copyfile2str(FILE* fp, char* tempstr){
    if(!fp || !tempstr){
        return false;
    }
    int count=0; // count hyphens for an undefined case: the file contains more lines than BRDSZ+1
    char buffer[BUFFERSIZE]={0};
    while(count++<=BRDSZ && fgets(buffer,BUFFERSIZE,fp)){
        for(int i=0;i<(int)strlen(buffer);i++){
            if(buffer[i]=='\n' || buffer[i]=='\r' || buffer[i]==' ' \
            || buffer[i]=='\t' || buffer[i] =='f'|| buffer[i]=='\v'){ // skip newlines and spaces
                buffer[i]=0;
            }else if(!('A'<=buffer[i] && buffer[i]<='Z')){
                return false;
            }
        }
        if(!strapd(tempstr,MAXSTR+1,buffer)){ // need +1 to remove the final hyphen
            fclose(fp);
            return false;
        }
        if(!strapd(tempstr,MAXSTR+1,"-")){ // i can't find a simpler way :(
            fclose(fp);
            return false;
        }
    }
    tempstr[strlen(tempstr)-1]=0; // to remove the final hyphen
    if(!isvalid(tempstr)){
        return false;
    }
    return true;
}

bool strapd(char* dest, int destsize, const char* source){
    // append string source to string dest
    if(!dest || !source){
        return false;
    }
    int remaining=destsize-strlen(dest)-1; 
    if (remaining<=0) {
        return false;
    }
    strncat(dest, source, remaining);
    return true;
}

state* str2state(const char* str){
    if(!str || strlen(str)==0){
        return NULL;
    }
    state* s=(state*)calloc(1,sizeof(state));
    if(!s){
        return NULL;
    }
    s->list=(board**)calloc(MAXBRDS,sizeof(board*));
    if(!s->list){
        free(s);
        return NULL;
    }
    board* init = str2board(str);
    if (!init) {
        free(s->list);
        free(s);
        return NULL;
    }
    s->list[0]=init;
    s->list[0]->parent=-1; // to avoid unexpected behaviour when printing
    s->moves=0;
    return s;
}

board* str2board(const char* str){
    if(!isvalid(str)){
        return NULL;
    }
    board* b = (board*)calloc(1, sizeof(board));
    if(!b){
        return NULL;
    }
    b->hawk=str[0];
    for(int j=0;j<BRDSZ;j++){
        for(int i=0;i<BRDSZ;i++){
            b->board[j][i]=EMPTY;
        }
    }
    if(!copystr2board(b,str)){
        return NULL;
    }
    updatelocked(b);
    b->hash=hashcode(b);
    return b;
}

bool copystr2board(board* b, const char* str){
    if(!b || !str){
        return false;
    }
    // count dashes to decide which line to begin with
    int count=0;
    int k=0;
    while(str[k]){
        if(str[k]=='-'){
            count++;
        }
        k++;
    }
    k=1;
    int i=0;
    int j=BRDSZ-count-1;
    while(str[k] && j<BRDSZ){
        if(str[k]=='-'){
            j++;
            i=0;
        }else{
            b->board[j][i++]=str[k];
        }
        k++;
    }
    return true;
}

bool isvalid(const char* str){
    int len=str?strlen(str):0; // null pointer also leads to length 0
    if(len==0 || len==2 || str[0]=='-' || str[len-1]=='-' || (len>1 && str[1]!='-')){
        return false;
    }
    if(len==1){
        return 'A'<=str[0] && str[0]<='Z'; 
    }
    // use loops to realize the regex (-[A-Z]{0,6}){0,6}
    int segcount=0, seglength=-1, index=0;
    for(int k=2;k<len;k++){ // k starts from 2, to skip str[1]=='-'
        if(str[k]=='-'){
            if(seglength==-1){
                seglength=index; // when more than 1 segment, update seglength to compare
            }else if(seglength!=index){ 
                return false; // index is the length of current segment, seglength is previous segment's
            }
            if (++segcount >= BRDSZ) {
                return false;  // segcount counts the number of segments, update whenever a '-' presents
            }
            index=0; // a '-' means a new segment starts, reset index
        }else if('A'<=str[k] && str[k]<='Z'){
            if(++index>BRDSZ){
                return false;
            }
        }else{ // when there are chars other than '-' or A-Z
            return false;
        }
    }
    return index == seglength || seglength == -1; // seglength==-1 indicates there is only 1 segment
}

void updatelocked(board* b){
    for(int i=0;i<BRDSZ;i++){
        bool locked=true;
        for(int j=1;j<BRDSZ && locked;j++){
            if(b->board[j-1][i]!=EMPTY && b->board[j][i]!=b->board[j-1][i]){
                locked=false;
            }
        }
        b->locked[i]=locked;
    }
}

int solve(state* s, bool verbose){
    if(!s){
        return false;
    }
    if(win(s->list[0])){
        if (verbose) {
            tracksteps(s->list[0], s);
        }
        freestate(s);
        return s->moves;
    }
    int index=1;
    int levelcount=1; // it equals 1 initially because we have only one node for the 1st level
    int nextlevelsize=0;
    bool found = false;
    for (int i = 0; i < index && index < MAXBRDS && !found; i++) {
        int index0=index;
        childboards(i, s, &index, &found);
        nextlevelsize=nextlevelsize+index-index0;
        if(--levelcount==0){
            s->moves++;
            levelcount=nextlevelsize;
            nextlevelsize=0;
        }
        if(found){
            s->moves++;
        }
    }
    if(!found){
        freestate(s);
        return INTERROR;
    }else{
        if(verbose){
            board* solution = s->list[index-1];
            tracksteps(solution,s);
        }
        freestate(s);
        return s->moves;
    }
}

void tracksteps(board* b, state* s){
    if(!b){
        return;
    }
    if(b->parent!=-1){
        tracksteps(s->list[b->parent],s);
    }
    printboard(b,1);
}

bool childboards(int parent, state* s, int* index, bool* found) {
    if (!s || !s->list[parent] || *index >= MAXBRDS || *found) {
        return false;
    }
    for (int i = 0; i < BRDSZ; i++) {
        if (!(s->list[parent])->locked[i]) {
            board* child = (board*)malloc(sizeof(board));
            if (!child) {
                return false;
            }
            if (!memcpy(child, s->list[parent], sizeof(board))) {
                free(child);
                return false;
            }
            push(child, i); 
            updatelocked(child);
            child->hash=hashcode(child);
            child->parent = parent;           
            if (exists(s, child, *index) == *index) { 
                s->list[*index] = child;
                (*index)++;
                if (win(child)) {
                    *found = true;
                    return true;
                }
            } else {
                free(child); 
            }

            if (*found) {
                return true;
            }
        }
    }
    return true;
}

bool push(board* b, int column){
    if(!b){
        return false;
    }
    char newhawk=b->board[BRDSZ-1][column];
    for(int i=BRDSZ-1;i>0;i--){
        b->board[i][column]=b->board[i-1][column];
    }
    b->board[0][column]=EMPTY;
    for(int i=BRDSZ-1;i>=0;i--){
        if(b->board[i][column]==EMPTY){
            b->board[i][column]=b->hawk;
            b->hawk=newhawk;
            return true;
        }
    }
    return false;
}

int exists(state* s, board* b, int index){
    if(!s || !b){
        return INTERROR;
    }
    for(int k=0;k<index;k++){
        if(equals(b, s->list[k])){
            return k;
        }
    }
    return index;
}

bool equals(board* b1, board* b2){
    if(!b1 || !b2){
        return false;
    }
    if(b1->hash!=b2->hash){
        return false;
    }
    if(b1->hawk!=b2->hawk){
        return false;
    }
    if (memcmp(b1->board, b2->board, sizeof(b1->board))) {
        return false;
    }
    return true;
}

long long hashcode(board* b) {
    long long hash;
    memcpy(&hash, (const char*)b->board + sizeof(b->board) - sizeof(long long), sizeof(long long));
    return hash;
}

bool win(board* b){
    for(int i=0;i<BRDSZ;i++){
        if(!b->locked[i]){
            return false;
        }
    }
    return true;
}

// only use in tests
bool board2str(board* b, char* buffer){
    if(!b || !buffer){
        return false;
    }
    buffer[0]=b->hawk;
    buffer[1]='-';
    int k=2;
    for(int j=0;j<BRDSZ;j++){
        for(int i=0;i<BRDSZ;i++){
            if(b->board[j][i]!=EMPTY){
                buffer[k++]=b->board[j][i];
            }
        }
        if(buffer[k-1]!='-'){
            buffer[k++]='-';
        }
    }
    buffer[k-1]=0;
    return true;
}

void printboard(board* b, int mode){
    if(!b){
        return;
    }
    if(mode==0){
        printf("%c\n",b->hawk);
        for(int j=0;j<BRDSZ;j++){
            for(int i=0;i<BRDSZ;i++){
                printf("%c ",b->board[j][i]);
            }
            printf("\n");
        }
    }else{
        for(int j=0;j<BRDSZ;j++){
            bool printed=false;
            for(int i=0;i<BRDSZ;i++){
                if(b->board[j][i]!=EMPTY){
                    printf("%c ",b->board[j][i]);
                    printed=true;
                }
            }
            if(printed){
                printf("\n");
            }
        }
    }
    printf("\n");
}


void freestate(state* s){
    if(!s){
        return;
    }
    for(int i=0;i<MAXBRDS && s->list[i]!=NULL;i++){
        free(s->list[i]);
    }
    free(s->list);
}


void test(void){

    assert(!isvalid(NULL));
    assert(isvalid("A"));                        
    assert(isvalid("Z"));
    assert(!isvalid("."));
    assert(!isvalid("\n"));
    assert(!isvalid("1"));
    assert(!isvalid(" "));
    assert(!isvalid("-"));
    assert(!isvalid("AA"));
    assert(!isvalid("A-"));                      
    assert(!isvalid("-A"));                     
    assert(!isvalid("A--A"));
    assert(!isvalid("A- -A"));
    assert(isvalid("A-A"));                      
    assert(isvalid("A-B-C")); 
    assert(isvalid("A-B-C-D-E-F"));              
    assert(isvalid("A-B-C-D-E-F-G"));   
    assert(isvalid("A-B-B-B-B-B-B")); 
    assert(isvalid("T-XY-XY-XY-XY-XY-XY"));          
    assert(isvalid("A-ABC"));                    
    assert(isvalid("A-ABC-XYZ"));    
    assert(isvalid("A-ABCDEF-ABCDEF"));              
    assert(isvalid("A-AAA-AAA-AAA-AAA"));        
    assert(isvalid("A-AAA-AAA-AAA-AAA-AAA-AAA"));
    assert(isvalid("Z-XYZ-XYZ-XYZ-XYZ-XYZ-XYZ"));
    assert(isvalid("A-ABC-DEF-GHI-JKL-MNO-PQR")); 
    assert(!isvalid("A-AAA-AAA-AAA-AAA-AAA-AAA-AAA"));
    assert(isvalid("A-ABCDEF-ABCDEF-ABCDEF-ABCDEF-ABCDEF-ABCDEF"));    
    assert(!isvalid("A-BC-DEF"));            
    assert(!isvalid("A-ABCDEFG"));                
    assert(!isvalid("A-XYZABCD"));                
    assert(!isvalid("A-XY-Z-XY"));    
    assert(!isvalid("A-Z-XY-XY"));   
    assert(!isvalid("A-XY-XY-Z"));          
    assert(!isvalid("A-XY-XY-XY-ABC-XY"));    
    assert(!isvalid("A-XYZ-XY-ABCD-XY-ZY"));    
    assert(!isvalid("A-1")); 
    assert(!isvalid("A-xyz"));  

    char str[100]={0};
    strcpy(str,"test1");
    assert(strapd(str,100,"-test2"));
    assert(!strcmp(str,"test1-test2"));
    strcpy(str,"");
    assert(strapd(str,100,"-test2"));
    assert(!strcmp(str,"-test2"));
    strcpy(str,"NULL");
    assert(strapd(str,100,"-test2"));
    assert(!strcmp(str,"NULL-test2"));
    strcpy(str,"NULL");
    assert(strapd(str,100,""));
    assert(!strcmp(str,"NULL"));     

    board* b=(board*)calloc(1,sizeof(board));
    for(int i=0;i<BRDSZ;i++){
        b->locked[i]=1;
    }
    assert(win(b));
    b->locked[BRDSZ-1]=0;
    assert(!win(b));
    b->locked[BRDSZ-1]=1;
    b->locked[0]=0;
    assert(!win(b));
    free(b);
    
    state* s;
    // basic normal case 
    s=str2state("A-ABC-CBA");
    assert(s->list[0]);
    assert(!s->moves);
    assert(!s->list[1]);
    assert((s->list[0])->hawk=='A');
    assert((s->list[0])->parent==-1);
    board2str(s->list[0],str);
    assert(!strcmp(str,"A-ABC-CBA"));
    for(int i=0;i<BRDSZ;i++){
        str[i]=(s->list[0])->locked[i]+'0';
    }
    str[BRDSZ]=0;
    assert(!strcmp(str,"010111"));
    freestate(s);
    free(s);
    
    
    // edge cases: wrong input string    
    assert(!str2board(""));
    assert(!str2state(""));    
    assert(!str2board("12345"));
    assert(!str2state("12345"));    
    assert(!str2board("A-1"));
    assert(!str2state("A-1"));
    
    // edge case: empty    
    s=str2state("A");
    assert(s->list[0]);
    assert(!s->moves);
    assert(!s->list[1]);
    assert((s->list[0])->hawk=='A');
    assert((s->list[0])->parent==-1);
    board2str(s->list[0],str);
    assert(!strcmp(str,"A"));
    for(int i=0;i<BRDSZ;i++){
        str[i]=(s->list[0])->locked[i]+'0';
    }
    str[BRDSZ]=0;
    assert(!strcmp(str,"111111"));
    freestate(s);
    free(s);
    
    // only a row
    s=str2state("X-ABCDEF");
    assert(s->list[0]);
    assert(!s->moves);
    assert(!s->list[1]);
    assert((s->list[0])->hawk=='X');
    assert((s->list[0])->parent==-1);
    board2str(s->list[0],str);
    assert(!strcmp(str,"X-ABCDEF"));
    for(int i=0;i<BRDSZ;i++){
        str[i]=(s->list[0])->locked[i]+'0';
    }
    str[BRDSZ]=0;
    assert(!strcmp(str,"111111"));
    freestate(s);
    free(s);
    
    // fully occupied left 3 columns
    s=str2state("A-AAA-AAA-AAA-AAA-AAA-AAA");
    assert(s->list[0]);
    assert(!s->moves);
    assert(!s->list[1]);
    assert((s->list[0])->hawk=='A');
    assert((s->list[0])->parent==-1);
    board2str(s->list[0],str);
    assert(!strcmp(str,"A-AAA-AAA-AAA-AAA-AAA-AAA"));
    for(int i=0;i<BRDSZ;i++){
        str[i]=(s->list[0])->locked[i]+'0';
    }
    str[BRDSZ]=0;
    assert(!strcmp(str,"111111"));
    freestate(s);
    free(s);
    
    s=str2state("A-ABC");
    board* b1=str2board("A-ABC-CBA");
    board* b2=str2board("A-ABC-CBA");
    board* b3=str2board("A-ABC-CBA-ACB");
    s->list[1]=b1;
    s->list[2]=b2;
    s->list[3]=b3;
    assert(!equals(b1,NULL));
    assert(!equals(NULL,NULL));
    assert(equals(b1,b2));
    assert(equals(b1,b1));
    assert(equals(s->list[0],s->list[0]));
    assert(!equals(s->list[0],b2));
    assert(!equals(s->list[0],b1));
    assert(3==exists(s,b3,3));
    assert(1==exists(s,b2,2));
    assert(1==exists(s,b2,1));
    assert(-1==exists(s,NULL,10));
    freestate(s);
    free(s);
    
    // manually solving, test push and updatelocked functions
    b=str2board("A-ABC-CAB");
    assert(b->locked[0]==0);
    assert(b->locked[1]==0);
    assert(b->locked[2]==0);
    assert(b->locked[3]==1);
    assert(b->locked[4]==1);
    assert(b->locked[5]==1);
    assert(!win(b));
    assert(push(b,0));
    assert(!push(NULL,3));
    strcpy(str,"");
    assert(board2str(b,str));
    assert(!strcmp(str,"C-ABC-AAB"));
    updatelocked(b);
    assert(b->locked[0]==1);
    assert(!win(b));
    assert(push(b,2));
    strcpy(str,"");
    assert(board2str(b,str));
    assert(!strcmp(str,"B-ABC-AAC"));
    updatelocked(b);
    assert(b->locked[2]==1);
    assert(!win(b));
    assert(push(b,1));
    strcpy(str,"");
    assert(board2str(b,str));
    assert(!strcmp(str,"A-ABC-ABC"));
    updatelocked(b);
    assert(b->locked[1]==1);
    assert(win(b));
    free(b);
    
    // automatically solve, test childboards function
    s=str2state("A-ABC-CAB");
    int index=1;
    bool found=false;
    childboards(0,s,&index,&found);
    assert(index==4 && !found);
    strcpy(str,"");
    assert(board2str(s->list[1],str));
    assert(!strcmp(str,"C-ABC-AAB"));
    strcpy(str,"");
    assert(board2str(s->list[2],str));
    assert(!strcmp(str,"A-AAC-CBB"));
    strcpy(str,"");
    assert(board2str(s->list[3],str));
    assert(!strcmp(str,"B-ABA-CAC"));
    for(int i=1;!found;i++){
        childboards(i,s,&index,&found);
    }
    strcpy(str,"");
    assert(win(s->list[index-1]));
    assert(board2str(s->list[index-1],str));
    assert(!strcmp(str,"A-ABC-ABC"));
    freestate(s);
    free(s);
    
    
    char* relpath="";
    char path[100]={0};
    
    strcpy(path, relpath);
    strcpy(str, "");
    strapd(path, 100, "0moves.brd");
    assert(file2str(path, str));
    assert(!strcmp(str, "A-B"));
    s=str2state(str);
    assert((s->list[0])->parent==-1);
    //assert(0==solve(s,false));
    freestate(s);
    free(s);
    
    strcpy(path,relpath);
    strcpy(str,"");
    strapd(path,100,"2moves.brd");
    assert(file2str(path,str));
    assert(!strcmp(str,"A-ABC-ABC-ABC-CBA"));
    s=str2state(str);
    //assert(2==solve(s,false));
    freestate(s);
    free(s);
    
    strcpy(path,relpath); 
    strcpy(str,"");
    strapd(path,100,"4moves.txt");
    assert(file2str(path,str));
    assert(!strcmp(str,"O-COMS-COMS-COMS-CMMS-CSSO"));
    s=str2state(str);
    //assert(4==solve(s,false));
    freestate(s);
    free(s);
    
    strcpy(path, relpath);
    strcpy(str, "");
    strapd(path, 100, "9moves.brd");
    assert(file2str(path, str));
    assert(!strcmp(str, "X-OHHI-OIHI-OOIX-HXIX"));
    s=str2state(str);
    //assert(9==solve(s,false));    
    freestate(s);
    free(s);
    
    strcpy(path, relpath);
    strcpy(str, "");
    strapd(path, 100, "10moves.brd");
    assert(file2str(path, str));
    assert(!strcmp(str, "C-AAB-ABB-CCB-CAC-ABC"));
    s=str2state(str);
    //assert(10==solve(s,false));
    freestate(s);
    free(s);
    
    strcpy(path, relpath);
    strcpy(str, "");
    strapd(path, 100, "11moves.brd");
    assert(file2str(path, str));
    assert(!strcmp(str, "A-ABB-ACB-CAC-CBC-ABC"));
    s=str2state(str);
    //assert(11==solve(s,false));    
    freestate(s);
    free(s);
    
    strcpy(path,relpath);
    strcpy(str,"");
    strapd(path,100,"imposs.brd");
    assert(file2str(path,str));
    assert(!strcmp(str,"A-BC-DE"));
    s=str2state(str);
    //assert(-1==solve(s,false));    
    freestate(s);
    free(s);
    
    // this test will be removed since it used my own test file
    strcpy(path,relpath);
    strcpy(str,"");
    strapd(path,100,"10lines.txt");
    assert(file2str(path,str));
    assert(!strcmp(str,"A-AAAAAA-BBBBBB-CCCCCC-DDDDDD-EEEEEE-FFFFFF"));
    // above test will be removed since it used my own test file
    
    
}
