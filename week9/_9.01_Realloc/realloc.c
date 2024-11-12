#include "specific.h"
#include "../arr.h"

/* Creates the empty array */
arr* arr_init(void){
    arr* l = (arr*)calloc(1, sizeof(arr));
    if (!l) {
        return NULL;
    }
    l->a = (int*)calloc(INITSIZE, sizeof(int));
    if (!l->a) {
        free(l);
        return NULL;
    }
    l->size=INITSIZE;
    return l;
}

/* Similar to l[n] = i, safely resizing if required */
void arr_set(arr *l, int n, int i){
// Setting an element out of bounds reallocs the array to make it valid
    if(!l){
        return;
    }
    if(n<0){
        printf("no negative index allowed\n");
        return;
    }
    if(n>=l->size){
        int newsize=n+1;
        l->a=(int*)realloc(l->a,newsize*sizeof(int));
        l->size=newsize;
    }
    l->a[n]=i;
}
/* Similar to = l[n] */

int arr_get(arr *l, int n){
// Getting an element out-of-bounds is an error
    assert(n<l->size);
    assert(n>=0);
    return l->a[n];
}
/* Clears all space used, and sets pointer to NULL */

void arr_free(arr **l){
    free((*l)->a);
    free(*l);
    *l=NULL;
}
