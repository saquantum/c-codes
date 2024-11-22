#define _CRT_SECURE_NO_WARNINGS
/* A 'tree 27' implementation
   of the Dictionary ADT */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

   // 26 letters, plus the '
#define ALPHA 27
#define BUFFERSIZE 200
#define MAXSTR 50


// You'd normally not expose this structure
// to the user, and it's members should *never*
// be used in e.g. driver.c
struct dict {
    // 'Down' pointers next letter of word a-z or '
    struct dict* dwn[ALPHA];
    /* The parent pointer, useful for
       traversing back up the tree */
    struct dict* up;
    // Is this node the end of a word?
    bool terminal;
    // Store occurences of the *same* word
    // Only used in terminal nodes
    int freq;
};
typedef struct dict dict;

// Creates new dictionary
dict* dict_init(void);

/* Top of Dictionary = p,
   add word str. Return false
   if p or str is NULL, or if word
   is already in the dictionary.
   True otherwise.
*/
bool dict_addword(dict* p, const char* wd);

/* The total number of nodes
   in the tree. */
int dict_nodecount(const dict* p);

/* Total number of times that any words
   have been added into the tree =
   sum of freq count of all terminals.*/
int dict_wordcount(const dict* p);

/* Returns the dict* where str is
   marked as 'terminal', or else NULL.
*/
dict* dict_spell(const dict* p, const char* str);

/* Frees all memory used by dictionary p.
   Sets the original pointer back to NULL */
void dict_free(dict** p);

/* Returns number of times most common
   word in dictionary has been added
   (when you insert a word and it already
   exists, increment the count)
*/
int dict_mostcommon(const dict* p);

/* CHALLENGE1
   For two nodes, count the nodes that separate them */
unsigned dict_cmp(dict* p1, dict* p2);

/* CHALLENGE2
   For dictionary 'p', and word 'wd', find the
   path down to the most frequently used word
   below this node, adding these letters to 'ret'.
   (In the event of ties, use the word that comes
   first alphabetically). */
void dict_autocomplete(const dict* p, const char* wd, char* ret);

void test(void);

bool __isvalid(const char* wd);
int __char2num(char c);
void __freenodes(dict* p);
void __countfreq(const dict* p, int* count);
void __countnode(const dict* p, int* count);
dict* __findword(const dict* p, const char* str);
void __findmostcommon(const dict* p, int* mc);
int __compare(char* s1, char* s2);
char* __node2str(dict* p);
void __findautocomplete(dict* p, const char* wd, int* mc, dict** dest);

int main(void)
{

    test();

    dict* d = NULL;
    char str[MAXSTR];

    // No words are in empty tree
    assert(dict_spell(d, "the") == NULL);
    // No nodes in empty tree
    assert(dict_nodecount(NULL) == 0);
    assert(dict_wordcount(NULL) == 0);


    d = dict_init();
    assert(dict_addword(d, "car"));
    assert(dict_addword(d, "cart"));
    assert(dict_addword(d, "part"));
    assert(dict_nodecount(d)==9);
    assert(dict_wordcount(d)==3);
    assert(dict_mostcommon(d)==1);
    dict* q1 = dict_spell(d, "car");
    dict* q2 = dict_spell(d, "part");
    assert(dict_cmp(q1, q2)==7);
    // It's unsigned
    assert(dict_cmp(q2, q1)==7);
    // 2 steps up from 'carter' is 'cart'
    dict_autocomplete(d, "car", str);
    // Most frequently stored word after car is car+t
    assert(strcmp(str, "t")==0);
    dict_free(&d);

    
    d = dict_init();
    // Should be a non-NULL address
    assert(d);
    // Top node always exists
    assert(dict_nodecount(d)==1);
    assert(dict_wordcount(d)==0);
    // Can't add a NULL string
    assert(dict_spell(d, NULL)==NULL);

    // 'car' isn't in the tree
    assert(dict_spell(d, "car")==NULL);
    // So add it
    assert(dict_addword(d, "car"));
    // It's there now
    assert(dict_spell(d, "car"));
    // Top node + 'c' + 'a' + 'r'
    assert(dict_nodecount(d)==4);
    assert(dict_wordcount(d)==1);
    
    // carted isn't in there
    assert(dict_spell(d, "carted")==NULL);
    // Put it in
    assert(dict_addword(d, "carted"));
    // It is now
    assert(dict_spell(d, "carted"));
    // 'car' -> 'carted' is 3 extra nodes
    assert(dict_nodecount(d)==7);
    assert(dict_wordcount(d)==2);

    // Cart isn't there as a terminal word
    assert(dict_spell(d, "cart")==NULL);
    // Put it in (case-insensitive)
    assert(dict_addword(d, "Cart"));
    // It's now there
    assert(dict_spell(d, "cart"));
    // No new nodes were created
    assert(dict_nodecount(d)==7);
    assert(dict_wordcount(d)==3);

    // Cart'd isn't there as a terminal word
    assert(dict_spell(d, "cart'd")==NULL);
    // Put it in
    assert(dict_addword(d, "cart'd"));
    // It's now there
    assert(dict_spell(d, "Cart'd"));
    // New nodes were created
    assert(dict_nodecount(d)==9);
    assert(dict_wordcount(d)==4);

    // Only one of each word at the moment
    assert(dict_mostcommon(d)==1);
    // Just increments the freq variable
    assert(!dict_addword(d, "cart"));
    // Now 'cart' has been added twice
    assert(dict_mostcommon(d)==2);
    // But no new nodes were created
    assert(dict_nodecount(d)==9);
    // Fifth word
    assert(dict_wordcount(d)==5);

    // Pointer to the bottom of cart...
    dict* p = dict_spell(d, "cart");
    assert(p);

    // Add some new words
    dict_addword(d, "par");
    dict_addword(d, "part");
    dict_addword(d, "parted");
    dict_addword(d, "parter");
    // 7 new nodes: p+a+r+t+e+d+r
    assert(dict_nodecount(d)==16);
    // 5 car prefixed + 4 par prefixed
    assert(dict_wordcount(d)==9);
    dict_free(&d);
    assert(d==NULL);

    /*
    #define DICTFILES 3
    // unique words : wordle has no apostrophes
    // but english_65197 does
    // Lots of repeated words : p-and-p-words
    char dictnames[DICTFILES][MAXSTR] = {"wordle.txt", "english_65197.txt", "p-and-p-words.txt"};
    int nodec[DICTFILES] = {5640, 161558, 18792};
    int mostc[DICTFILES] = {1, 1, 4331};
    dict* dcts[DICTFILES];
    for(int i=0; i<DICTFILES; i++){
       d = dict_init();
       dcts[i] = d; // Keep dictionaries for later
       assert(d);
       // Word count
       int wc = 0;
       FILE* fp = fopen(dictnames[i], "rt");
       if(!fp){
          fprintf(stderr, "Cannot open word file?\n");
          exit(EXIT_FAILURE);
       }
       while(fgets(str, MAXSTR, fp) != NULL){
          char str2[MAXSTR];
          sscanf(str, "%s", str2);
          // If unique word file, it's not inserted yet ...
          if(mostc[i] == 1){
             assert(dict_spell(d, str2)==NULL);
          }
          //printf(">%s<\n", str2);
          dict_addword(d, str2);
          wc++;
          // ... but it is now
          assert(dict_spell(d, str2));
       }
       fclose(fp);
       // No word is added twice
       assert(dict_mostcommon(d)==mostc[i]);
       // Hard to test for ...
       assert(dict_nodecount(d)==nodec[i]);
       assert(dict_wordcount(d)==wc);
    }
    */
    

    /* Leave this commented out to begin with
    // !!!!!!!!!!!!!!!!!!!!!!!
    // 10% : DICT_AUTOCOMPLETE
       d = dict_init();
       assert(d);
       dict_addword(d, "carting");
       dict_addword(d, "carter");
       dict_addword(d, "carting");
       dict_addword(d, "carted");
       dict_addword(d, "carting");
       dict_addword(d, "cart");
       dict_addword(d, "carting");
       dict_addword(d, "car");
       dict_addword(d, "carting");

       // We've made sure carting is
       // a frequently-occuring word ...
       dict_autocomplete(d, "c", str);
       assert(strcmp(str, "arting")==0);
       dict_autocomplete(d, "carte", str);
       // Alphabetically carted not carter
       assert(strcmp(str, "d")==0);

       // Use the Pride & Prejudice
       // dictionary built above
       p = dcts[2];
       dict_autocomplete(p, "t", str);
       // 'the' is most common word that
       // can be found from 't'
       assert(strcmp(str, "he")==0);
       // But given 'the' what comes after it?
       dict_autocomplete(p, "thei", str);
       // their ...
       assert(strcmp(str, "r")==0);
       // This story is about the bennet family:
       dict_autocomplete(p, "ben", str);
       assert(strcmp(str, "net")==0);

    // !!!!!!!!!!!!!!
    // 10% : DICT_CMP
       dict* p1 = dict_spell(d, "cart");
       dict* p2 = dict_spell(d, "carter");
       // 2 steps up from 'carter' is 'cart'
       assert(dict_cmp(p1, p2)==2);
       p1 = dict_spell(d, "carted");
       // 1 step up to 'carte' and 1 back down again
       assert(dict_cmp(p1, p2)==2);

       p1 = dict_spell(dcts[0], "aback");
       p2 = dict_spell(dcts[0], "zonal");
       // 5 moves to top, 5 moves back down again
       assert(dict_cmp(p1, p2)==10);
       dict_free(&d);
    */
    /*
       // Free up all those dictionaries
       for(int i=0; i<DICTFILES; i++){
          dict_free(&dcts[i]);
       }
    */
    return 0;
}



dict* dict_init(void) {
    dict* root = calloc(1, sizeof(dict));
    if (!root) {
        return NULL;
    }
    return root;
}

bool __isvalid(const char* wd) {
    if (!wd) {
        return false;
    }
    int i = 0;
    while (wd[i] && i<MAXSTR) {
        bool valid = isalpha(wd[i]) || wd[i] == '\'';
        if (!valid) {
            return false;
        }
        i++;
    }
    return i < MAXSTR;
}

int __char2num(char c) {
    if ('a' <= c && c <= 'z') {
        return c - 'a';
    }
    else if ('A' <= c && c <= 'Z') {
        return c - 'A';
    }
    else if (c == '\'') {
        return ALPHA - 1;
    }
    return -1;
}

bool dict_addword(dict* p, const char* wd) {
    if (!p || !wd) {
        return false;
    }
    if (!__isvalid(wd)) {
        return false;
    }
    if (strlen(wd) == 0) {
        return false;
    }
    int i = 0;
    while (wd[i]) {
        int next = __char2num(wd[i]);
        if (next == -1) {
            return false;
        }
        if (!p->dwn[next]) {
            p->dwn[next] = dict_init();
            if (!p->dwn[next]) {
                return false;
            }
            p->dwn[next]->up = p;
        }
        p = p->dwn[next];
        i++;
    }
    p->terminal = true;
    (p->freq)++;
    return p->freq>1;
}

void __freenodes(dict* p) {
    if (!p) {
        return;
    }
    for (int i = 0; i < ALPHA; i++) {
        __freenodes(p->dwn[i]);
    }
    free(p);
}

void dict_free(dict** p) {
    if (!p || !(*p)) {
        return;
    }
    __freenodes(*p);
    *p = NULL;
}

void __countfreq(const dict* p, int* count) {
    if (!p) {
        return;
    }
    for (int i = 0; i < ALPHA; i++) {
        __countfreq(p->dwn[i], count);
    }
    if (p->terminal) {
        (*count) += p->freq;
    }
}

int dict_wordcount(const dict* p) {
    if (!p) {
        return 0;
    }
    int count = 0;
    __countfreq(p, &count);
    return count;
}

void __countnode(const dict* p, int* count) {
    if (!p) {
        return;
    }
    (*count)++;
    for (int i = 0; i < ALPHA; i++) {
        __countnode(p->dwn[i], count);
    }
}

int dict_nodecount(const dict* p) {
    if (!p) {
        return 0;
    }
    int count = 0;
    __countnode(p, &count);
    return count;
}


dict* __findword(const dict* p, const char* str) {
    if (!p || !str) {
        return NULL;
    }
    if (*str == '\0') {
        if (p->terminal) {
            return p;
        }
        else {
            return NULL;
        }
    }
    int next = __char2num(*str);
    if (!p->dwn[next]) {
        return NULL;
    }
    return __findword(p->dwn[next], str + 1);
}

dict* dict_spell(const dict* p, const char* str) {
    if (!p || !str) {
        return NULL;
    }
    if (!__isvalid(str)) {
        return NULL;
    }
    dict* d = p;
    return __findword(d, str);
}

void __findmostcommon(const dict* p, int* mc) {
    if (!p) {
        return;
    }
    if (p->terminal) {
        *mc = *mc < p->freq ? p->freq : *mc;
    }
    for (int i = 0; i < ALPHA; i++) {
        __findmostcommon(p->dwn[i], mc);
    }
}

int dict_mostcommon(const dict* p) {
    if (!p) {
        return 0;
    }
    int mc = 0;
    dict* d = p;
    __findmostcommon(d, &mc);
    return mc;
}

char* __node2str(dict* p) {
    if (!p) {
        return NULL;
    }
    char buffer[BUFFERSIZE] = { 0 };
    char* b = buffer;
    while (p && p->up) {
        dict* temp = p;
        p = p->up;
        bool flag = false;
        int i = 0;
        for (; i < ALPHA && !flag; i++) {
            if (p->dwn[i] == temp) {
                flag = true;
            }
        }
        if (!flag) {
            return NULL;
        }
        if (i == ALPHA) {
            *b = '\'';
        }else {
            *b = (--i) + 'a';
        }
        b++;
    }
    int len = strlen(buffer);
    char* str = calloc(1 + len, sizeof(char));
    if (!str) {
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        str[i] = buffer[len - i - 1];
    }
    return str;
}

// CHALLENGE1
unsigned dict_cmp(dict* p1, dict* p2) {
    if (!p1 || !p2) {
        return (unsigned)-1;
    }
    char* s1 = __node2str(p1);
    char* s2 = __node2str(p2);
    if (!s1 || !s2) {
        free(s1);
        free(s2);
        return (unsigned)-1;
    }
    // find the common prefix of s1 and s2
    unsigned len1 = strlen(s1);
    unsigned len2 = strlen(s2);
    unsigned min = len1 < len2 ? len1 : len2;
    unsigned i = 0;
    bool flag = false;
    while (i < min && s1[i] == s2[i]) {
        i++;
    }
    free(s1);
    free(s2);
    return (len1 - i) + (len2 - i);
}

// return 1: s1<s2 0: s1=s2 -1: s1>s2
int __compare(char* s1, char* s2) {
    int len1 = !s1 ? 0 : strlen(s1);
    int len2 = !s2 ? 0 : strlen(s2);
    if (len1 != len2) {
        return len2 - len1;
    }
    int i = 0;
    while (i < len1) {
        if (s1[i] != s2[i]) {
            return s2[i] - s1[i];
        }
        i++;
    }
    return 0;
}

void __findautocomplete(dict* p, const char* wd, int* mc, dict** dest) {
    if (!p) {
        return;
    }
    if (p->terminal) {
        char* current_word = __node2str(p);
        if (!current_word) {
            return;
        }
        if (!strcmp(wd, current_word)) {
            // skip
        }else if (p->freq > *mc) {
            *mc = p->freq;
            *dest = p;
        }
        else if (p->freq == *mc) {
            char* s1 = __node2str(p);
            char* s2 = __node2str(*dest);
            if (!s1 || !s2) {
                free(s1);
                free(s2);
                return;
            }
            if (__compare(s1, s2) > 0) {
                *dest = p;
            }
            free(s1);
            free(s2);
        }
        free(current_word);
    }
    for (int i = 0; i < ALPHA; i++) {
        __findautocomplete(p->dwn[i],wd, mc, dest);
    }
}

// CHALLENGE2
void dict_autocomplete(const dict* p, const char* wd, char* ret) {
    if (!p || !wd || !ret || !__isvalid(wd)) {
        if (ret) {
            ret[0] = 0;
        }
        return;
    }
    int mc = 0;
    dict* dest = NULL;
    __findautocomplete((dict*)p, wd, &mc, &dest);
    if (!dest) {
        ret[0] = 0;
        return;
    }
    char* str = __node2str(dest);
    if (!str) {
        exit(1);
    }
    int i = 0;
    while (wd[i] && str[i] && wd[i] == str[i]) {
        i++;
    }
    strcpy(ret, str + i);
    free(str);
}

void test(void) {
    dict* p = dict_init();
    char* tempstr1[BUFFERSIZE] = {0};
    strcpy(tempstr1, "cart");
    assert(dict_addword(p, tempstr1));
    dict* p1 = dict_spell(p, tempstr1);
    assert(p1);
    char* str1 = __node2str(p1);
    assert(!strcmp(str1, tempstr1));

    char* tempstr2[BUFFERSIZE] = { 0 };
    strcpy(tempstr2, "part");
    assert(dict_addword(p, tempstr2));
    dict* p2 = dict_spell(p, tempstr2);
    assert(p2);
    char* str2 = __node2str(p2);
    assert(!strcmp(str2, tempstr2));

    free(str1);
    free(str2);
    dict_free(p);
}
