#include "bst.h"

void test(){
    bst* b=bst_init();
    assert(b);
    int a=10;
    assert(bst_insert(b, "int", &a));
    assert(bst_get(b, "int", &a));
    a=8;
    assert(bst_insert(b, "int", &a));
    assert(bst_get(b, "int", &a));
    a=13;
    assert(bst_insert(b, "int", &a));
    assert(bst_get(b, "int", &a));
    a=7;
    assert(bst_insert(b, "int", &a));
    assert(bst_get(b, "int", &a));
    a=9;
    assert(bst_insert(b, "int", &a));
    assert(bst_get(b, "int", &a));
    a=11;
    assert(bst_insert(b, "int", &a));
    assert(bst_get(b, "int", &a));
    a=14;
    assert(bst_insert(b, "int", &a));
    assert(bst_get(b, "int", &a));
    a=12;
    assert(bst_insert(b, "int", &a));
    assert(bst_get(b, "int", &a));
    a=15;
    assert(bst_insert(b, "int", &a));
    assert(bst_get(b, "int", &a));
    
    /*
    int depth=1;
    char*** strings = __bst2strings(b, &depth, b->datatype);
    assert(__depth_left_array(strings, depth, 5, 3)==3);
    assert(__depth_left_array(strings, depth, 7, 3)==3);
    assert(__depth_left_array(strings, depth, 0, 0)==2);
    assert(__depth_left_array(strings, depth, 0, 1)==2);
    assert(__depth_left_array(strings, depth, 1, 1)==2);
    assert(__depth_left_array(strings, depth, 1, 3)==-1);
    assert(__depth_left_array(strings, depth, 3, 3)==-1);
    */
    
    void (*style)(char***, int)=__compactstyle;
    printBST(b,style);
    
    
    
    int c=13;
    assert(bst_delete(b, "int", &c));
    printBST(b,style);
    
    bst_free(b);
    
    b=bst_init();
    assert(b);
    
    double d=10.1415926;
    assert(bst_insert(b, "double", &d));
    assert(bst_get(b, "double", &d));
    d=9.556;
    assert(bst_insert(b, "double", &d));
    assert(bst_get(b, "double", &d));
    d=9.57;
    assert(bst_insert(b, "double", &d));
    assert(bst_get(b, "double", &d));
    d=11.5;
    assert(bst_insert(b, "double", &d));
    assert(bst_get(b, "double", &d));
    d=11.4;
    assert(bst_insert(b, "double", &d));
    assert(bst_get(b, "double", &d));
    d=11.39;
    assert(bst_insert(b, "double", &d));
    assert(bst_get(b, "double", &d));
    d=11.38;
    assert(bst_insert(b, "double", &d));
    assert(bst_get(b, "double", &d));
    d=11.45;
    assert(bst_insert(b, "double", &d));
    assert(bst_get(b, "double", &d));
    d=8.534;
    assert(bst_insert(b, "double", &d));
    assert(bst_get(b, "double", &d));
    d=13;
    assert(bst_insert(b, "double", &d));
    assert(bst_get(b, "double", &d));
    d=15;
    assert(bst_insert(b, "double", &d));
    assert(bst_get(b, "double", &d));
    d=14;
    assert(bst_insert(b, "double", &d));
    assert(bst_get(b, "double", &d));
    
    printBST(b,style);
    
    double e=11.50;
    assert(bst_delete(b, "double", &e));
    
    printBST(b,style);
    
    bst_free(b);
    
    char str[BUFFERSIZE]={0};
    
    strcpy(str,"");
    strcpy(str,"abc");
    strist(str,"123",0);
    assert(!strcmp(str,"123abc")); 
    strcpy(str,"");
    strcpy(str,"abc");
    strist(str,"123",1);
    assert(!strcmp(str,"a123bc"));
    strcpy(str,"");
    strcpy(str,"abc");
    strist(str,"123",3);
    assert(!strcmp(str,"abc123"));
    strcpy(str,"");
    strcpy(str,"abc");
    strist(str,"123",4);
    assert(!strcmp(str,"abc 123"));
    strcpy(str,"");
    strcpy(str,"abc");
    strist(str,"123",6);
    assert(!strcmp(str,"abc   123"));
    strcpy(str,"");
    strcpy(str,"abc");
    strist_withhyphens(str,"123",6);
    assert(!strcmp(str,"abc---123"));
}

int main(){
    test();
}
