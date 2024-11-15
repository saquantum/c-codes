struct soll{
    node* start;
    node* end;
    orgtype type;
    int size;
}

typedef struct node{
    char* data;
    int freq;
    struct node* next;
}node;

// typedef enum{none, mtf, transpose} orgtype;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "../soll.h"


// find a node by index
node* __nodeByIndex(soll* s, int i);

