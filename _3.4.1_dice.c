#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

#define MAXTHROW 6
#define NUMDICE 5
#define TESTS 10000000

void randomthrow(int d[NUMDICE]);
bool histo_has(const int h[MAXTHROW], const int n);
void makehist(const int d[NUMDICE], int h[MAXTHROW]);
bool hists_same(const int h1[MAXTHROW], const int h2[MAXTHROW]);
bool isfullhouse(const int d[NUMDICE]);
bool is4ofakind(const int d[NUMDICE]);
void test();

int main() {

	srand(time(NULL));
	test();

	int dice[NUMDICE];
	int k4 = 0;
	int fh = 0;
	int i;

	for (i = 0; i < TESTS; i++) {
		randomthrow(dice);
		if (isfullhouse(dice)) {
			fh++;
		}
		if (is4ofakind(dice)) {
			k4++;
		}
	}
	printf("FH=%.2f%% 4oK=%.2f%%\n", (double)fh * 100.0 / (double)TESTS, (double)k4 * 100.0 / (double)TESTS);


	return 0;
}

/* Fill the array d with random numbers 1..6 */
void randomthrow(int d[NUMDICE]) {
	int i = 0;
	for (i = 0; i < NUMDICE; i++) {
		d[i] = 1 + rand() % MAXTHROW;
	}
}

/* Decide if the number n occurs anywhere in the histogram h */
bool histo_has(const int h[MAXTHROW], const int n) {
	for (int i = 0; i < MAXTHROW; i++) {
		if (h[i] == n) {
			return true;
		}
	}
	return false;
}

/* Compute a histogram, given a dice hand */
void makehist(const int d[NUMDICE], int h[MAXTHROW]) {
	int i = 0;

	/* since the array is called by reference and we do not
	   create a new array, thus must first initialise the array */ 
	for (i = 0; i < MAXTHROW; i++) {
		h[i] = 0;
	}

	for (i = 0; i < NUMDICE; i++) {
		h[d[i]-1]++;
	}
}

/* Check that the histograms h1 & h2 are the same */
bool hists_same(const int h1[MAXTHROW], const int h2[MAXTHROW]) {
	for (int i = 0; i < MAXTHROW; i++) {
		if (h1[i] != h2[i]) {
			return false;
		}
	}
	return true;
}

/* Does this hand have 2 lots of one number and 3 lots of another */
bool isfullhouse(const int d[NUMDICE]) {
	bool flag2 = false;
	bool flag3 = false;

	int h[MAXTHROW] = { 0 };
	makehist(d, h);

	for (int i = 0; i < MAXTHROW; i++) {
		if (h[i] == 2) {
			flag2 = true;
		}
		else if (h[i] == 3) {
			flag3 = true;
		}
	}
	return flag2 && flag3;
}

/* Does this hand have 4 lots of one number and 1 of another ? */
bool is4ofakind(const int d[NUMDICE]) {
	bool flag4 = false;

	int h[MAXTHROW] = { 0 };
	makehist(d, h);

	for (int i = 0; i < MAXTHROW; i++) {
		if (h[i] == 4) {
			flag4 = true;
		}
	}
	return flag4;
}

void test() {


	int i, j;
	int h1[MAXTHROW] = { 0,0,0,0,0,5 };
	int h2[MAXTHROW] = { 0,0,5,0,0,0 };
	int h3[MAXTHROW] = { 0,2,0,0,3,0 };
	int h4[MAXTHROW] = { 2,0,3,0,0,0 };
	int h5[MAXTHROW] = { 3,2,0,0,0,0 };
	int h6[MAXTHROW] = { 0,0,0,2,3,0 };
	int h7[MAXTHROW] = { 4,1,0,0,0,0 };
	int h8[MAXTHROW] = { 0,0,0,0,1,4 };
	int h9[MAXTHROW] = { 0,0,0,0,0,0 };
	int d1[NUMDICE] = { 1,1,1,2,2 };
	int d2[NUMDICE] = { 5,4,5,4,5 };
	int d3[NUMDICE] = { 2,1,1,1,1 };
	int d4[NUMDICE] = { 6,6,6,6,5 };
	int d5[NUMDICE] = { 6,6,6,6,5 };

	for (i = 0; i < 100; i++) {
		randomthrow(d5);
		for (j = 0; j < NUMDICE; j++) {
			assert(d5[j]>=1 && d5[j]<=MAXTHROW);
		}
		makehist(d5, h9);
		for (j = 0; j < MAXTHROW; j++) {
			assert(h9[j] >= 0 && h9[j] <= NUMDICE);
		}
	}
	assert(hists_same(h1, h1) == true);
	assert(hists_same(h5, h5) == true);
	assert(hists_same(h1, h2) == false);
	assert(hists_same(h4, h5) == false);
	makehist(d1, h9); assert(hists_same(h9, h5));
	makehist(d2, h9); assert(hists_same(h9, h6));
	makehist(d3, h9); assert(hists_same(h9, h7));
	makehist(d4, h9); assert(hists_same(h9, h8));
	assert(histo_has(h1, 5) == true);
	assert(histo_has(h1, 0) == true);
	assert(histo_has(h1, 2) == false);
	assert(histo_has(h2, 5) == true);
	assert(histo_has(h2, 0) == true);
	assert(histo_has(h2, 2) == false);
	assert(histo_has(h3, 3) == true);
	assert(histo_has(h3, 2) == true);
	assert(histo_has(h3, 1) == false);
	assert(histo_has(h4, 3) == true);
	assert(histo_has(h4, 2) == true);
	assert(histo_has(h4, 1) == false);
	assert(isfullhouse(d1) == true);
	assert(isfullhouse(d2) == true);
	assert(is4ofakind(d1) == false);
	assert(is4ofakind(d2) == false);
	assert(isfullhouse(d3) == false);
	assert(isfullhouse(d4) == false);
	assert(is4ofakind(d3) == true);
	assert(is4ofakind(d4) == true);

}
