#include "specific.h"
#include "../set.h"

/* Create empty set */
set* set_init(void){
    set* s = (set*)calloc(1, sizeof(set));
    if (!s) {
        return NULL;
    }
    s->a = (int*)calloc(INITSIZE, sizeof(int));
    if (!s->a) {
        free(s);
        return NULL;
    }
    s->size=INITSIZE;
    s->length=0;
    return s;
}
/* Create new set, copied from another */
set* set_copy(set* s){
    if(!s){
        return calloc(1,sizeof(set));
    }
    set* new=calloc(1,sizeof(set));
    new->size=s->size;
    new->length=s->length;
    new->a = (int*)calloc(s->size, sizeof(int));
    if (!new->a) {
        free(new);
        return NULL;
    }
    memcpy(new->a, s->a, s->size*sizeof(int));
    return new;
}
/* Create new set, copied from an array of length n*/
set* set_fromarray(int* a, int n){
    if(!a){
        return calloc(1,sizeof(set));
    }
    set* s=calloc(1,sizeof(set));
    int size=2*n<INITSIZE?INITSIZE:2*n;
    s->a=calloc(size,sizeof(int));
    int index=0;
    for(int j=0;j<n;j++){
        bool duplicate = false;
        for(int i=0;i<j && !duplicate;i++){
            if(a[i]==a[j]){
                duplicate=true;
            }
        }
        if(!duplicate){
            s->a[index]=a[j];
            index++;
        }
    }
    s->length=index;
    s->size=size;
    return s;
}

/* Basic Operations */
/* Add one element into the set */
void set_insert(set* s, int l){
    if(!s){
        return;
    }
    if(-1==_set_contains(s,l)){
        if (s->length >= s->size) {
            s->size *= 2;
            s->a = (int*)realloc(s->a, s->size * sizeof(int));
            if (!s->a) return;  // Handle memory allocation failure
        }
        s->a[s->length]=l;
        s->length++;
    }
}
/* Return size of the set */
int set_size(set* s){
    if(!s){
        return 0;
    }
    return s->length;
}
/* Returns true if l is in the array, false elsewise */
int set_contains(set* s, int l){
    if(!s){
        return 0;
    }
    for(int i=0;i<s->length;i++){
        if(s->a[i]==l){
            return 1;
        }
    }
    return 0;
}

int _set_contains(set* s, int l){
    if(!s){
        return -1;
    }
    for(int i=0;i<s->length;i++){
        if(s->a[i]==l){
            return i;
        }
    }
    return -1;
}

/* Remove l from the set (if it's in) */
void set_remove(set* s, int l){
    if(!s){
        return;
    }
    int index;
    if((index=_set_contains(s,l))!=-1){
        for(int i=index;i<s->length-1;i++){
            s->a[i]=s->a[i+1];
        }
        s->length--;
    }
}
/* Remove one element from the set - there's no
   particular order for the elements, so any will do */
int set_removeone(set* s){
    if(!s){
        return 0;
    }
    if(s->length==0){
        return 0;
    }
    s->length--;
    return s->a[s->length-1];
}

/* Operations on 2 sets */
/* Create a new set, containing all elements from s1 & s2 */
set* set_union(set* s1, set* s2){
    int* a=calloc(s1->length+s2->length,sizeof(int));
    memcpy(a,s1->a,s1->length*sizeof(int));
    memcpy(a+s1->length,s2->a,s2->length*sizeof(int));
    set* s = set_fromarray(a,s1->length+s2->length);
    free(a);
    return s;
}

/* Create a new set, containing all elements in both s1 & s2 */
set* set_intersection(set* s1, set* s2){
    set* s=set_copy(s1);
    if(!s2){
        s->length=0;
        return s;
    }
    int i=0;
    while(i<s->length){
        if(!set_contains(s2,s->a[i])){
            set_remove(s,s->a[i]);
        }else{
            i++;
        }
    }
    return s;
}

void _printset(set *s){
    if(!s){
        return;
    }
    printf("s->a = ");
    for(int i=0;i<s->length;i++){
        printf("%d ",s->a[i]);
    }
    printf("\n");
}

/* Finish up */
/* Clears all space used, and sets pointer to NULL */
void set_free(set** s){
    if(s==NULL){
        return;
    }
    free((*s)->a);
    free(*s);
    *s=NULL;
}
