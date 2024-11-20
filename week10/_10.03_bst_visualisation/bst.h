// i could split these lengthy functions into shorter ones
// but i can't come up with names for them. which is really hard.
// and there are way too many private functions already here.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>
#include <math.h>

typedef struct node{
    struct node* left;
    struct node* right;
    void* data;
}node;

typedef struct{
    node* root;
    int size;
    char* datatype;
}bst;

#define BUFFERSIZE 2000
#define EMPTY " " // when datatype is char and insert EMPTY or null, every print style goes catastrophically wrong.

void test();


// public methods
bst* bst_init();
node* bst_get(bst* b, char* datatype, void* data);
bool bst_insert(bst* b, char* datatype, void* data);
bool bst_deletemin(bst* b);
bool bst_delete(bst* b, char* datatype, void* data);
void bst_free(bst* b);
void printBST(bst* b, void (*style)(char***,int));

// private methods: manipulating bst
node* __get(node* n, char* datatype, void* data);
int __compare(char* datatype, void* data1, void* data2);
node* __makenode(char* datatype, void* data);
node* __insert(node* n, char* datatype, void* data);
node* __deletemin(node* n);
node* __delete(node* n, char* datatype, void* data);
node* __min(node* n);
int __getsize(char* datatype);
char*** __bst2strings(bst* b, int* depth, char* datatype);
void __free(node* n);

// private methods: printing styles
void __compactstyle(char*** strings, int depth);
void __treestyle(char*** strings, int depth);
void __arraystyle(char*** strings, int depth);
void __inorderstyle(char*** strings, int depth);

// private methods: who wants to visualize bst
bool __entry(int* x, int* y, int rows);
bool __printspaces(char* str, int n);
bool __bound(int depth, int x, int y);
bool __isempty(char*** strings, int x, int y);
void __printVerticalLine(bool** printed, char*** strings, char** compact, int depth, int x, int y);
int __efficient_depth(char*** strings, int depth, int x, int y);
void __relative_root(int depth, int* x, int* y);
int __critical_width(char*** strings, char** compact, int depth, int x, int y);
void __inorderTraversal_recursion(char*** strings, int depth, int x, int y);
void __compactstyle_recursion(bool** printed, char*** strings, char** compact, int depth, int x, int y);

// string manipulation
char* substring(const char* source, int s, int e);
bool strist(char* dest, const char* src, int pos);
bool strist_withhyphens(char* dest, const char* src, int pos);

// read file
char*** file2strings(FILE* fp, int* depth);

