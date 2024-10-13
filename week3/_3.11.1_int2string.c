#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h> 

#define MAXSIZE 12 // this is because 2^31=2147483648 has 10 digits, plus a sign and a null character

void int2string(int n, char s[MAXSIZE]);
void initarray(char s[], int len);
void test();

int main() {

	test();

	int n = 123;
	char s[MAXSIZE];
	int2string(n, s);
	int i = 0;
	while (s[i] != '\0') {
		printf("%c", s[i]);
		i++;
	}
}

void int2string(int n, char s[MAXSIZE]) {
	initarray(s, MAXSIZE);

	int sign = 1;
	if (n < 0) {
		sign = -1;
		n = -n;
	}

	int arr[MAXSIZE];
	int i = 0;
	do {
		arr[i] = n % 10;
		n = n/10;
		i++;
	} while (n > 0);

	if (sign == 1) {
		int k;
		for (k = 0; k < i; k++) {
			s[k] = (char)(arr[i - k - 1] + '0');
		}
		s[k] = '\0';
		return;
	}
	int k;
	s[0] = '-';
	for (k = 0; k < i; k++) {
		s[k+1] = (char)(arr[i - k - 1] + '0');
	}
	s[k+1] = '\0';
}

void initarray(char s[], int len) {
	for (int i = 0; i < len; i++) {
		s[i] = 0;
	}
}

void test() {
	char s[MAXSIZE];

	int2string(0, s);
	assert(strcmp(s, "0")==0);

	int2string(10, s);
	assert(strcmp(s, "10") == 0);

	int2string(99, s);
	assert(strcmp(s, "99") == 0);

	int2string(124, s);
	assert(strcmp(s, "124") == 0);

	int2string(3141, s);
	assert(strcmp(s, "3141") == 0);

	int2string(-1000, s);
	assert(strcmp(s, "-1000") == 0);

	int2string(2147483647, s);
	assert(strcmp(s, "2147483647") == 0);

}
