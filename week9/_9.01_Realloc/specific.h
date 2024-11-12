#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../arr.h"
/*
A resizeable indexed array ADT. Here:
1. Setting an element out of bounds reallocs the array to make it valid
2. Getting an element out-of-bounds is an error
*/

#define INITSIZE 16

struct arr{
    int* a;
    int size;
};

/* Creates the empty array */
arr* arr_init(void);
/* Similar to l[n] = i, safely resizing if required */
void arr_set(arr *l, int n, int i);
/* Similar to = l[n] */
int arr_get(arr *l, int n);
/* Clears all space used, and sets pointer to NULL */
void arr_free(arr **l);
