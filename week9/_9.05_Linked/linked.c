#include "specific.h"
#include "../soll.h"

// Initialize a Self-Organising Linked List
soll* soll_init(orgtype type) {
    soll* s = calloc(1, sizeof(soll));
    if (!s) return NULL;
    s->type = type;
    return s;
}

// Add a new element
void soll_add(soll* s, char* str) {
    if (!s || !str) return;
    node* n = calloc(1, sizeof(node));
    if (!n) return;

    n->data = calloc(strlen(str) + 1, sizeof(char));
    if (!n->data) {
        free(n);
        return;
    }
    strcpy(n->data, str);  // Copy the string data into the node
    n->freq = 1;
    n->next = NULL;

    if (s->start == NULL) {
        s->start = n;
        s->end = n;
    } else {
        s->end->next = n;
        s->end = n;
    }
    s->size++;
}

// Find a node by index
node* __nodeByIndex(soll* s, long i) {
    if (!s || i >= s->size || i < 0) return NULL;
    node* n = s->start;
    for (long k = 0; k < i; k++) {
        n = n->next;
    }
    return n;
}

// Remove an element from the list
bool soll_remove(soll* s, char* str) {
    if (!s || !str) {
        return false;
    }
    node* n=s->start;
    node* np=NULL;

    if(!n){
        return false;
    }
    bool found=false;
    while (n && !found) {
        if (!strcmp(str, n->data)) {
            found = true;
        }
        if (!found) {
            np = n;
            n = n->next;
        }
    }
    if(found && np){
        np->next=n->next;
        if(!np->next){
            s->end=np;
        }
        free(n->data);
        free(n);
        s->size--;
    }else if(found && !np){
        s->start=n->next;
        free(n->data);
        free(n);
        s->size--;
    }
    return true;
}

// Check if an element is in the list, re-organizing if necessary
bool soll_isin(soll* s, char* str, long* cnt) {
    if (!s || !str || !cnt) return false;
    node* n = s->start;
    node* np = NULL;
    node* npp = NULL;
    bool found = false;

    *cnt=0;

    while (n && !found) {
        if (!strcmp(str, n->data)) {
            n->freq++;
            found = true;
        }
        if (!found) {
            npp = np;
            np = n;
            n = n->next;
            (*cnt)++;
        }
    }

    if (found && np) {
        if (s->type == mtf) {
            np->next = n->next;
            n->next = s->start;
            s->start = n;
            if (np->next == NULL) {
                s->end = np;
            }
        } else if (s->type == transpose) {
            if (!npp) {
                np->next = n->next;
                n->next = s->start;
                s->start = n;
                if (np->next == NULL) {
                    s->end = np;
                }
            } else {
                np->next = n->next;
                npp->next = n;
                n->next = np;
                if (np->next == NULL) {
                    s->end = np;
                }
            }
        }
    }
    return found;
}

// Get frequency of a specific element
int soll_freq(soll* s, char* str) {
    if (!s || !str) return 0;
    node* n = s->start;
    while (n) {
        if (!strcmp(str, n->data)) return n->freq;
        n = n->next;
    }
    return 0;
}

// Get the number of elements in the list
int soll_size(soll* s) {
    return s ? s->size : 0;
}

// Convert list to string format
void soll_tostring(soll* s, char* str) {
    if (!s || !str) return;
    strcpy(str,"");
    node* n = s->start;
    if(!n){
        return;
    }
    char buffer[1000];
    while (n) {
        sprintf(buffer,"%s(%d)|", n->data, n->freq);
        strcat(str, buffer);
        n = n->next;
    }
    str[strlen(str)-1]=0;
}

// Free all allocated memory
bool soll_free(soll* s) {
    if (!s) return true;
    node* p = s->start;
    while (p) {
        node* p0 = p->next;
        free(p->data);
        free(p);
        p = p0;
    }
    free(s);
    return true;
}
