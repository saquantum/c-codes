#include "../boolarr.h"
#include "specific.h"

 /* All elements initialised to "0" */
boolarr* boolarr_init(void){
    boolarr* ba=calloc(1,sizeof(boolarr));
    ba->a=calloc(INITSIZE,sizeof(unsigned char));
    ba->size=INITSIZE;
    ba->occupied_bits=0;
    ba->capacity_bits=ba->size*8-ba->occupied_bits;
    return ba;
}

/* Create boolarr based on string e.g. "1100001" */
boolarr* boolarr_initstr(const char* str){
    unsigned int size=INITSIZE<(strlen(str)+7)/8?(strlen(str)+7)/8:INITSIZE;
    boolarr* ba=calloc(1,sizeof(boolarr));
    ba->a=calloc(size,sizeof(unsigned char));
    ba->size=size;
    ba->occupied_bits=strlen(str);
    ba->capacity_bits=ba->size*8-ba->occupied_bits;
    // nth digit of packed bool array, should be n%8-th bit of n/8-th byte,
    // meaning we add 2^(n%8) to n/8-th byte, which is 1<<(n%8).
    
    int n=0;
    while(str[n]){
        if(str[n]=='1'){
            ba->a[n/8] |= 1<<(n%8);
        }
        n++;
    }
    return ba;
}

/* Return a deep copy */
boolarr* boolarr_clone(const boolarr* ba){
    boolarr* clone=calloc(1,sizeof(boolarr));
    clone->size=ba->size;
    clone->occupied_bits=ba->occupied_bits;
    clone->capacity_bits=ba->capacity_bits;
    
    clone->a = calloc(clone->size, sizeof(unsigned char));
    memcpy(clone->a,ba->a,ba->size*sizeof(unsigned char));
    return clone;
}

/* Get number of bits in array */
unsigned int boolarr_size(const boolarr* ba){
    if(!ba){
        return 0;
    }
    return ba->occupied_bits;
}

/* Return number of bits that are set true */
unsigned int boolarr_count1s(const boolarr* ba){
    if(!ba){
        return 0;
    }
    int count=0;
    for(unsigned int i=0;i<ba->occupied_bits;i++){
        count=ba->a[i/8] & (1<<(i%8))?count+1:count;
    }
    return count;
}

/* Set nth bit on/off */
bool boolarr_set(boolarr* ba, const unsigned int n, const bool b){
    if(!ba){
        return false;
    }
    unsigned int newsize=n/8+1;
    if(newsize>ba->size){
        ba->a=realloc(ba->a,newsize*sizeof(unsigned char));
        memset(ba->a + ba->size, 0, (newsize - ba->size) * sizeof(unsigned char));
        ba->size=newsize;
    }
    if(b){
        ba->a[n/8] |= 1<<(n%8);
    }else{
        ba->a[n/8] &= ~(1<<(n%8));
    }
    if(n+1>ba->occupied_bits){
        ba->occupied_bits=n+1;
        ba->capacity_bits=ba->size*8-ba->occupied_bits;
    }
    return true;
}
/* Get nth bit */
bool boolarr_get(const boolarr* ba, const unsigned int n, bool* b){
    if(!ba || !b){
        return false;
    }
    if(n>=ba->occupied_bits){
        return false;
    }
    *b = (ba->a[n / 8] & (1 << (n % 8))) ? true : false;
    return true;
}

/* Return if two arrays are the same (bitwise) */
bool boolarr_issame(const boolarr* b1, const boolarr* b2){
    if(!b1 && !b2){
        return true;
    }
    if(!b1 || !b2){
        return false;
    }
    if(b1->size!=b2->size || b1->occupied_bits!=b2->occupied_bits || b1->capacity_bits!=b2->capacity_bits){
        return false;
    }
    for(unsigned int i=0;i<b1->occupied_bits;i++){
        if((b1->a[i/8] & (1<<(i%8))) != (b2->a[i/8] & (1<<(i%8)))){
            return false;
        }
    }
    return true;
}

/* Store to string - rightmost bit is LSB */
bool boolarr_tostring(const boolarr* ba, char* str){
    if(!ba || !str){
        return false;
    }
    unsigned int i=0;
    for(;i<ba->occupied_bits;i++){
        str[i]=(ba->a[i / 8] & (1 << (i % 8))) ? '1' : '0';
    }
    str[i]=0;
    return true;
}

/* Print out array & meta info */
bool boolarr_print(const boolarr* ba){
    if(!ba){
        return false;
    }
    printf("size=%d, occupied bits=%d, capacity=%d\n",ba->size,ba->occupied_bits,ba->capacity_bits);
    return true;
}

/* Flip all bits */
bool boolarr_negate(boolarr* ba){
    if(!ba){
        return false;
    }
    for(unsigned int i=0;i<ba->occupied_bits;i++){
        ba->a[i / 8] ^= (1 << (i % 8));
    }
    return true;
}

/* Functions dealing with 2 bitwise-arrays */
/* Must be the same length */
boolarr* boolarr_bitwise(const boolarr* ba1, const boolarr* ba2, const logicalop l){
// typedef enum logicalop {or, and, xor} logicalop;
    if(!ba1 || !ba2){
        return NULL;
    }
    if(ba1->occupied_bits != ba2->occupied_bits){
        return NULL;
    }
    boolarr* ba=boolarr_clone(ba1);
    for (unsigned int i = 0; i < ba1->occupied_bits; i++) {
    
        unsigned int bit1 = ba1->a[i / 8] & (1 << (i % 8));
        unsigned int bit2 = ba2->a[i / 8] & (1 << (i % 8));
        unsigned int result_bit = 0;

        switch (l) {
            case 0:
                result_bit = bit1 | bit2;
                break;
            case 1:
                result_bit = bit1 & bit2;
                break;
            case 2:
                result_bit = bit1 ^ bit2;
                break;
            default:
                return NULL;
        }

        if (result_bit) {
            ba->a[i / 8] |= (1 << (i % 8));  // Set bit
        } else {
            ba->a[i / 8] &= ~(1 << (i % 8)); // Clear bit
        }
    }
    return ba;
}

/* Clears all space */
bool boolarr_free(boolarr* p){
    if(!p){
        return false;
    }
    free(p->a);
    free(p);
    return true;
}
