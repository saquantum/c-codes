#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define RED 1
#define BLACK 0
#define BUFFERSIZE 200

#define COLOUR_RED  "\x1B[31m"
#define COLOUR_NORMAL  "\x1B[0m"

struct node {
	char* word;
	struct node* left;
	struct node* right;
	bool colour; // the colour of the link from its parent node
	int freq;
	int totalnode;
	int totalfreq;
	int maxfreq;
};
struct rbt {
	struct node* root;
};
typedef struct node node;
typedef struct rbt rbt;

// public
rbt* dict_init();
void dict_free(rbt* r);
bool dict_addword(rbt* r, char* word);
int dict_nodecount(const rbt* r);
int dict_wordcount(const rbt* r);
int dict_mostcommon(const rbt* r);
node* dict_spell(const rbt* r, const char* wd);
unsigned dict_cmp(const rbt* r,node* n1, node* n2);
void dict_autocomplete(const rbt* r, const char* wd, char* ret);
void inorderTraversal(rbt* r);

// private
void __free(node* n);
node* __makenode(char* word, bool colour);
bool __isred(node* n);
bool __isvalid(const char* wd);
node* __rotateleft(node* left);
node* __rotateright(node* right);
void __updatedata(node* n);
int __compare(char* s1, char* s2);
void __flipcolour(node* center);
node* __insert(node* n, char* word); 
node* __trackword(node* n, const char* word);
node* __LCA(const rbt* r, node* n1, node* n2);
unsigned __count_path_length(node* root, node* target);
bool __hasprefix(node* n, char* word);
node* __findprefix(node* n, const char* word);
void __findautocomplete(node* n, const char* word, node** dest, int* mc);
void __inorder(node* n);

void test();
int main() {
	test();
}

rbt* dict_init() {
	return (rbt*)calloc(1, sizeof(rbt));
}

void dict_free(rbt* r) {
	__free(r->root);
}

void __free(node* n) {
	if (!n) {
		return;
	}
	__free(n->left);
	__free(n->right);
	free(n->word);
	free(n);
}

bool __isvalid(const char* wd) {
	if (!wd) {
		return false;
	}
	int i = 0;
	while (wd[i] && i < BUFFERSIZE) {
		bool valid = isalpha(wd[i]) || wd[i] == '\'';
		if (!valid) {
			return false;
		}
		i++;
	}
	return i < BUFFERSIZE;
}

node* __makenode(char* word, bool colour) {
	if (!word || !*word) {
		return NULL;
	}
	node* n = calloc(1,sizeof(node));
	if (!n) {
		return NULL;
	}
	n->word = calloc(strlen(word) + 1, sizeof(char));
	if (!n->word) {
		free(n);
		return NULL;
	}
	strcpy(n->word, word);
	n->colour = colour;
	n->freq = 1;
	n->totalfreq = 1;
	n->totalnode = 1;
	n->maxfreq = 1;
	return n;
}

bool __isred(node* n) {
	if (!n) {
		return false;
	}
	return n->colour;
}

void __updatedata(node* n) {
	int l_totalnode = n->left ? n->left->totalnode : 0;
	int l_totalfreq = n->left ? n->left->totalfreq : 0;
	int l_maxfreq = n->left ? n->left->maxfreq : 0;
	int r_totalnode = n->right ? n->right->totalnode : 0;
	int r_totalfreq = n->right ? n->right->totalfreq : 0;
	int r_maxfreq = n->right ? n->right->maxfreq : 0;
	n->totalnode = l_totalnode + r_totalnode + 1;
	n->totalfreq = l_totalfreq + r_totalfreq + n->freq;
	// maxfreq is the largest among left, right and current node
	n->maxfreq = l_maxfreq > r_maxfreq ? l_maxfreq : (r_maxfreq > n->freq ? r_maxfreq : n->freq);
}

node* __rotateleft(node* left) {
	node* right = left->right;
	left->right = right->left;
	right->left = left;
	right->colour = left->colour; // transfer the colour of the link from parent
	left->colour = RED; // now the red link is a left child link of right node
	// freq is unaltered, update all metadata
	// must update left first!
	__updatedata(left);
	__updatedata(right);
	return right; // right node will be linked to their parent
}

node* __rotateright(node* right) {
	node* left = right->left;
	right->left = left->right;
	left->right = right;
	left->colour = right->colour; 
	right->colour = RED; 
	__updatedata(right);
	__updatedata(left);
	return left; 
}

void __flipcolour(node* center) {
	center->left->colour = BLACK;
	center->right->colour = BLACK;
	center->colour = RED;
}
// here we first lexico then by length, which is different from 27-way trie
// to improve autocompletion
int __compare(char* s1, char* s2) {
	int len1 = !s1 ? 0 : strlen(s1);
	int len2 = !s2 ? 0 : strlen(s2);
	int min = len1 < len2 ? len1 : len2;
	int i = 0;
	while (i < min) {
		if (s1[i] != s2[i]) {
			return s1[i] - s2[i];
		}
		i++;
	}
	return len2 - len1;
}

// logic of rotations:
// 1. if two red links form a shape <, bring the bottom vertex into upper edge of <, so two red links form a shape /
// 2. for shape /, bend it so becomes ∧
// 3. for ∧, set both edge link black and parent link red
node* __insert(node* n, char* word) {
	if (!n) {
		return __makenode(word,RED);
	}
	int cmp = __compare(word, n->word);
	if (cmp < 0) {
		n->left = __insert(n->left, word);
	}else if (cmp > 0) {
		n->right = __insert(n->right, word);
	}else {
		n->freq++;
		__updatedata(n);
	}
	if (__isred(n->right) && !__isred(n->left)) {
		n = __rotateleft(n);
	}
	if (__isred(n->left) && __isred(n->left->left)) {
		n = __rotateright(n);
	}
	if (__isred(n->left) && __isred(n->right)) {
		__flipcolour(n);
	}
	__updatedata(n);
	return n;
}

bool dict_addword(rbt* r, char* word) {
	if (!r || !word || !*word || !__isvalid(word)) {
		return false;
	}
	r->root = __insert(r->root, word);
	if (!r->root) {
		return false;
	}
	r->root->colour = BLACK; // root node is always black
	return true;
}

int dict_nodecount(const rbt* r) {
	if (!r || !r->root) {
		return 0;
	}
	return r->root->totalnode;
}

int dict_wordcount(const rbt* r) {
	if (!r || !r->root) {
		return 0;
	}
	return r->root->totalfreq;
}

int dict_mostcommon(const rbt* r) {
	if (!r || !r->root) {
		return 0;
	}
	return r->root->maxfreq;
}

node* __trackword(node* n, const char* word) {
	if (!n || !n->word || !word || !*word || !__isvalid(word)) {
		return NULL;
	}
	int cmp = __compare(word, n->word);
	if (cmp < 0) {
		return __trackword(n->left,word);
	}else if (cmp > 0) {
		return __trackword(n->right, word);
	}else {
		return n;
	}
}

node* dict_spell(const rbt* r, const char* word) {
	if (!r || !r->root || !word || !*word || !__isvalid(word)) {
		return NULL;
	}
	return __trackword(r->root, word);
}

// find the least common ancestor of n1 and n2 starting from root
node* __LCA(const rbt* r, node* n1, node* n2) {
	if (!r || !n1 || !n2 || !n1->word || !n2->word) {
		return NULL;
	}
	node* p = r->root;
	while (p) {
		int cmp1 = __compare(n1->word, p->word);
		int cmp2 = __compare(n2->word, p->word);
		if (cmp1 < 0 && cmp2 < 0) {
			p = p->left;
		}
		else if (cmp1 > 0 && cmp2 > 0) {
			p = p->right;
		}
		else {
			return p;
		}
	}
	return NULL;
}

unsigned __count_path_length(node* root, node* target) {
	if (!root || !target || !root->word || !target->word) {
		return (unsigned)-1;
	}
	unsigned length = 0;
	node* p = root;
	while (p) {
		int cmp = __compare(target->word, p->word);
		if (cmp < 0) {
			p = p->left;
			length++;
		}
		else if (cmp > 0) {
			p = p->right;
			length++;
		}
		else {
			return length;
		}
	}
	return (unsigned)-1;
}

unsigned dict_cmp(const rbt* r, node* n1, node* n2) {
	if (!r || !n1 || !n2 || !n1->word || !n2->word) {
		return (unsigned)-1;
	}
	node* lca = __LCA(r, n1, n2);
	if (!lca) {
		return (unsigned)-1;
	}
	unsigned dist1 = __count_path_length(lca, n1);
	unsigned dist2 = __count_path_length(lca, n2);
	if (dist1 == (unsigned)-1 || dist2 == (unsigned)-1) {
		return (unsigned)-1;
	}
	return dist1 + dist2;
}

// verify if n->word has word as its prefix
bool __hasprefix(node* n, char* word) {
	if (!n || !n->word || !word) {
		return false;
	}
	for (int i = 0; word[i]; i++) {
		// early exit: if n->word is shorted than word, or does not match.
		if (n->word[i]==0 || n->word[i] != word[i]) {
			return false;
		}
	}
	return true;
}

// if word is an actual word, the node returned should be it.
// if word is not an actual word, the node is the first word that contains it.
node* __findprefix(node* n, const char* word) {
	if (!n || !n->word || !word) {
		return NULL;
	}
	if (__hasprefix(n, word)) {
		return n;
	}
	int cmp = __compare(word, n->word);
	if (cmp < 0 ) {
		return __findprefix(n->left, word);
	}
	else if (cmp > 0) {
		return __findprefix(n->right, word);
	}
	return NULL;
}

// 1. for a root node of a subtree with prefix "word",
// not necessarily all of its child nodes have the same prefix.
// but if left child and right child share this prefix,
// then all nodes in this subtree share this prefix.
// hence we can use two modes to select in terms of scenario.
// 2. early exit: if current node has this prefix, and freq=maxfreq,
// then we can skip the whole subtree of this node.
void __findautocomplete(node* n, const char* word, node** dest, int* mc) {
	if (!n || !n->word || !word || !dest) {
		return;
	}
	if (__hasprefix(n, word) && strcmp(n->word, word)) {
		// the second condition is tie-breaking:
		// compare them by lexico order
		if (n->freq > *mc || (n->freq == *mc && __compare(n->word, (*dest)->word) < 0)) {
			*mc = n->freq;
			*dest = n;
		}
	}
	__findautocomplete(n->left, word, dest, mc);
	__findautocomplete(n->right, word, dest, mc);
}

// this method accepts empty string, since it's a valid prefix for any word.
// but it can't be NULL.
void dict_autocomplete(const rbt* r, const char* word, char* ret) {
	if (ret) {
		ret[0] = 0;
	}
	if (!r || !r->root || !word || !ret) {
		return;
	}
	node* subroot = __findprefix(r->root, word);
	if (!subroot) {
		return;
	}
	node* dest = NULL;
	int mc = 0;
	// traverse the whole subtree to update dest.
	__findautocomplete(subroot, word, &dest, &mc);
	if (!dest) {
		return;
	}
	int i = 0;
	while (word[i] && dest->word[i] && word[i] == dest->word[i]) {
		i++;
	}
	strcpy(ret, dest->word + i);
}

void __inorder(node* n) {
	if (!n) {
		return;
	}
	__inorder(n->left);
	printf("%s ",n->word);
	__inorder(n->right);
}

void inorderTraversal(rbt* r) {
	if (!r) {
		return;
	}
	__inorder(r->root);
}

void test() {

	char str[200] = { 0 };
	rbt* r = dict_init();
	dict_addword(r, "zeal");
	dict_addword(r, "application");
	dict_addword(r, "apple");
	dict_addword(r, "cart");
	dict_addword(r, "prefix");
	dict_addword(r, "prefix");
	dict_addword(r, "prefix");
	dict_addword(r, "bat");
	dict_addword(r, "cat");
	dict_addword(r, "part");
	dict_addword(r, "cailian");

	assert(dict_nodecount(r) == 9);
	assert(dict_wordcount(r) == 11);
	assert(dict_mostcommon(r) == 3);
	dict_autocomplete(r, "", str);
	assert(!strcmp(str, "prefix"));
	dict_autocomplete(r, "p", str);
	assert(!strcmp(str, "refix"));
	dict_autocomplete(r, "notfound", str); // Nonexistent prefix
	assert(str[0] == 0); // Should return an empty string
	dict_autocomplete(r, "ca", str);
	assert(!strcmp(str, "ilian"));

	node* result = dict_spell(r, "prefix");
	assert(result && !strcmp(result->word, "prefix") && result->freq == 3);

	result = dict_spell(r, "application");
	assert(result && !strcmp(result->word, "application") && result->freq == 1);

	result = dict_spell(r, "notfound");
	assert(result == NULL); // Word not in the dictionary

	dict_addword(r, "zeal"); // Add another "zeal"
	dict_addword(r, "zeal"); // Now "zeal" becomes the most common word
	dict_addword(r, "zeal"); // Now "zeal" becomes the most common word
	assert(dict_mostcommon(r) == 4); 

	dict_addword(r, ""); // Add empty string (invalid word)
	assert(dict_nodecount(r) == 9); // No change to total nodes
	dict_addword(r, "!@#$"); // Add invalid characters
	assert(dict_nodecount(r) == 9); // No change to total nodes

	dict_autocomplete(r, NULL, str); // Null prefix
	assert(str[0] == 0); // Should return an empty string

	dict_free(r);
}
