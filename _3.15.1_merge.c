#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h> 

#define MAXSIZE 100

int overlap(const char s1[], const char s2[]);
void substring(const char s[], int index1, int index2, char out[]);
void initarray(char s[], int len);
void strmerge(const char s1[], const char s2[], char s3[]);
void test();

int main() {

	test();

	char s1[] = "abcde ,";
	char s2[] = "cde ,fg";

	char s[MAXSIZE];
	strmerge(s1, s2, s);
	for (int i = 0; i < MAXSIZE; i++) {
		printf("%c", s[i]);
	}

	return 0;
}

void strmerge(const char s1[], const char s2[], char s3[]) {

	int len1 = strlen(s1);
	int len2 = strlen(s2);

	initarray(s3, MAXSIZE);

	char o1[MAXSIZE];
	char o2[MAXSIZE];
	char o3[MAXSIZE];

	int index = overlap(s1, s2);

	if (len1 > len2) { //the length of overlap is len2-index
		substring(s1, 0, (len1 - 1) - (len2 - index), o1);
		substring(s1, (len1 - 1) - (len2 - index) + 1, strlen(s1), o2);
		substring(s2, len2 - index, strlen(s2), o3);
	}
	else { // the length of overlap is len1-index
		substring(s1, 0, index-1, o1);
		substring(s1, index, strlen(s1), o2);
		substring(s2, len1 - index, strlen(s2), o3);
	}
	// merge the 3 pieces (o1, o2, o3) into 1 string (s3)
    int i = 0;
	while (o1[i] != '\0') {
		s3[i] = o1[i];
		i++;
	}
	while (o2[i-strlen(o1)] != '\0') {
		s3[i] = o2[i - strlen(o1)];
		i++;
	}
	while (o3[i - strlen(o1) - strlen(o2)] != '\0') {
		s3[i] = o3[i - strlen(o1) - strlen(o2)];
		i++;
	}
	s3[i] = '\0';
}

int overlap(const char s1[], const char s2[]) {
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int min = len1 < len2 ? len1 : len2;
	char temp1[MAXSIZE];
	char temp2[MAXSIZE];

	for (int i = 0; i < min; i++) {
		substring(s1, len1 - min + i, len1 - 1, temp1);
		substring(s2, 0, min - i - 1, temp2);

		if (!strcmp(temp1, temp2)) {
			return i;
		}
		initarray(temp1, MAXSIZE);
		initarray(temp2, MAXSIZE);
	}
	return min;
}

void substring(const char s[], int index1, int index2, char out[]) {
	int i;
	for (i = 0; i <= index2 - index1; i++) {
		out[i] = s[i + index1];
	}
	out[i] = '\0';
}

void initarray(char s[], int len) {
	for (int i = 0; i < len; i++) {
		s[i] = 0;
	}
}

void test() {
	assert(strlen("abc") == 3);

	char temp[MAXSIZE];

	initarray(temp, MAXSIZE);
	substring("abcd", 0, 2, temp);
	assert(strcmp(temp, "abc") == false);

	initarray(temp, MAXSIZE);
	substring("abcd", 1, 2, temp);
	assert(strcmp(temp, "bc") == false);

	initarray(temp, MAXSIZE);
	substring("abcd", 1, 1, temp);
	assert(strcmp(temp, "b") == false);

	initarray(temp, MAXSIZE);
	substring("abcd", 2, 3, temp);
	assert(strcmp(temp, "cd") == false);

	initarray(temp, MAXSIZE);
	substring("abcd", 0, 3, temp);
	assert(strcmp(temp, "abcd") == false);

	strmerge("Hello World!", "World! & Everyone.", temp);
	assert(strcmp(temp, "Hello World! & Everyone.") == false);

	strmerge("The cat sat", "sat on the mat.", temp);
	assert(strcmp(temp, "The cat sat on the mat.") == 0);

	strmerge("The cat sat on the mat", "The cat sat on the mat.", temp);
	assert(strcmp(temp, "The cat sat on the mat.") == 0);

	strmerge("One ", "Two", temp);
	assert(strcmp(temp, "One Two") == 0);

	strmerge("", "The cat sat on the mat.", temp);
	assert(strcmp(temp, "The cat sat on the mat.") == 0);

	strmerge("The cat sat on the mat.", "", temp);
	assert(strcmp(temp, "The cat sat on the mat.") == 0);

	strmerge("123412341234", "1234", temp);
	assert(strcmp(temp, "123412341234") == 0);

	strmerge("samsams", "samsabc", temp);
	assert(strcmp(temp, "samsamsabc") == 0);

	strmerge("sasasas", "sasbsms", temp);
	assert(strcmp(temp, "sasasasbsms") == 0);

}
