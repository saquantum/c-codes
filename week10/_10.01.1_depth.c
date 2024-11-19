#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define STRSIZE 5000

struct node{
	char c;
	struct node *left;
	struct node *right;
};
typedef struct node Node;

Node *MakeNode(char c);
void InsertRandom(Node *t, Node *n);
char *PrintTree(Node *t);
void freeTree(Node* n);
void depth(Node* n, int* record, int* dp);

int main(void)
{

   char c;
   Node *head = MakeNode('A');
   Node *n;

   srand(time(NULL));
   for(c = 'B'; c < 'G'; c++){
      n = MakeNode(c);
      InsertRandom(head, n);
   }
   int record=1;
   int dp=0;
   depth(head,&record,&dp);
   printf("depth=%d\n",dp);
   printf("%s\n", PrintTree(head));
   freeTree(head);
   return 0;
}

Node *MakeNode(char c)
{

   Node *n = (Node *)calloc(1, sizeof(Node));
   assert(n != NULL);
   n->c = c;
   return n;

}

void InsertRandom(Node *t, Node *n)
{

   if((rand()%2) == 0){ /* Left */
      if(t->left == NULL){
         t->left = n;
      }
      else{
         InsertRandom(t->left, n);
      }
   }
   else{ /* Right */
      if(t->right == NULL){
         t->right = n;
      }
      else{
         InsertRandom(t->right, n);
      }
   }

}

void depth(Node* n, int* record, int* dp){
    
    if(n->left){
        (*record)++;
        depth(n->left,record,dp);
    }
    if(n->right){
        (*record)++;
        depth(n->right,record,dp);
    }
    if(*dp<*record){
        *dp=*record;
    }
    (*record)--;
    
}

char *PrintTree(Node *t)
{

   char *str;

   assert((str = calloc(STRSIZE, sizeof(char))) != NULL);
   if(t == NULL){
      strcpy(str, "*");
      return str;
   }
   sprintf(str, "%c (%s) (%s)", t->c, PrintTree(t->left), PrintTree(t->right));
   return str;

}

void freeTree(Node* n){
    if(!n){
        return;
    }
    if(n->left){
        freeTree(n->left);
    }
    if(n->right){
        freeTree(n->right);
    }
    free(n);
}
