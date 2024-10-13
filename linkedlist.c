#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef int type;

typedef struct data {
	type n;
}data;

typedef struct node {
	data* d;
	struct node* next;
}node;

bool addnode2first(node** first, data* d);
node* delete(node** first, int n);
bool insertnode(node** first, data* d, int n);
node* nthnode(node* first, int n);
void freelist(node* first);
void printlinkedlist(node* first);
void printdata(data* d);

int main() {
	node* p = NULL;
	for (int i = 0; i < 10; i++) {
		data* d = (data*)malloc(sizeof(data));
		assert(d);
		d->n = i;
		addnode2first(&p, d);
	}
	//free(delete(&p, 0));
	printlinkedlist(p);
	freelist(p);
}

bool addnode2first(node** first, data* d) {
	node* new = (node*)malloc(sizeof(node));
	if (new == NULL) {
		return false;
	}
	new->next = *first;
	new->d = d;
	*first = new;
	return true;
}

bool insertnode(node** first, data* d, int n) {
	int i = 0;
	node* p = *first;
	if (n < 0) {
		return false;
	}
	if (n == 0) {
		return addnode2first(first, d);
	}
	while (p && i < n - 1) {
		p = p->next;
		i++;
	}
	if (p == NULL) {
		return false;
	}
	node* new = (node*)malloc(sizeof(node));
	if (new == NULL) {
		return false;
	}
	new->d = d;
	new->next = p->next;
	p->next = new;
	return true;
}

node* delete(node** first, int n) {
	int i = 0;
	node* p = *first;
	node* q = NULL;
	if (n == 0) {
		*first = p->next;
		return p;
	}
	while (p && i < n) {
		q = p;
		p = p->next;
		i++;
	}
	if (p == NULL || i != n) {
		return NULL;
	}
	q->next = p->next;
	return p;
}

node* nthnode(node* first, int n) {
	int i = 0;
	node* p = first;
	if (first = NULL || n < 0) {
		return false;
	}
	while (p && i < n) {
		p = p->next;
		i++;
	}
	return p;
}

int length(node* first) {
	int n = 0;
	node* p = first;
	while (p) {
		p = p->next;
		n++;
	}
	return n;
}

void freelist(node* first) {
	node* p = first;
	node* q = p;
	while (p) {
		q = p;
		p = p->next;
		free(q);
	}
}

void printlinkedlist(node* first) {
	node* p = first;
	while (p) {
		printdata(p->d);
		p = p->next;
	}
	printf("\n");
}

void printdata(data* d) {
	printf("%d ", d->n);
}

/*
deletenodebyvalue()
	findnode()
reverselist()
*/
