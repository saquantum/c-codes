#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

#define MAXTHROW 6
#define NUMDICE 5
#define TESTS 10000000

void randomthrow(int d[NUMDICE]);
bool histo_has(const int h[MAXTHROW],const int n);
void makehist(const int d[NUMDICE],int h[MAXTHROW]);
bool hists_same(const int h1[MAXTHROW],const int h2[MAXTHROW]);
bool isfullhouse(const int d[NUMDICE]);
bool is4ofakind(const int d[NUMDICE]);
void test(void);


/* Fill the array d with random numbers 1..6 */
void randomthrow(int d[NUMDICE]) {
	srand(time(NULL));
	for (int i = 0; i < NUMDICE; i++) {
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
	for (int i = 0; i < NUMDICE; i++) {
		h[d[i]]++;
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
