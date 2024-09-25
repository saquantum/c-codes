#include<stdio.h> 
#include<assert.h> 
#include<math.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

#define MAXSIZE 100

int let2code(char c);
void initarray(char s[], int len);
void soundex(const char s[], char out[MAXSIZE]);
void test();

int main() {
	test();
	char code[MAXSIZE];
	soundex("Wu", code);
	printf("%s\n",code);
	return 0;
}

void soundex(const char s[],char out[MAXSIZE]) {
	initarray(out, MAXSIZE);
	out[0] = toupper(s[0]);
	int i = 1;
	int pos = 1;
	while (s[i] != '\0' && pos<4) {
		if (i - 1 >= 0 && let2code(s[i - 1])== let2code(s[i])) { //skip
		}
		else if(i-2>=0 && let2code(s[i-1])==-1 && let2code(s[i - 2]) == let2code(s[i])) { //skip
		}
		else if(let2code(s[i]) == 0 || let2code(s[i]) == -1) { //skip
		}
		else {
			out[pos] = (char)(let2code(s[i])+'0');
			pos++;
		}
		i++;
	}
	if (strlen(out) < 4) {
		while (pos < 4) {
			out[pos] = '0';
			pos++;
		}
	}
}

void initarray(char s[], int len) {
	for (int i = 0; i < len; i++) {
		s[i] = 0;
	}
}

int let2code(char c) {
	c = tolower(c);
	if (c == 'b' || c == 'f' || c == 'p' || c == 'v') {
		return 1;
	}
	if (c == 'c' || c == 'g' || c == 'j' || c == 'k' || c == 'q' || c == 's' || c == 'x' || c == 'z') {
		return 2;
	}
	if (c == 'd' || c == 't'){
		return 3;
	}
	if (c == 'l') {
		return 4;
	}
	if (c=='m'||c=='n'){
		return 5;
	}
	if (c == 'r') {
		return 6;
	}
	if (c == 'h' || c == 'w') {
		return -1;
	}
	return 0;
}

void test() {
	char temp[MAXSIZE];

	initarray(temp, MAXSIZE);
	soundex("Washington", temp);
	assert(strcmp(temp,"W252") == false);

	initarray(temp, MAXSIZE);
	soundex("Wu", temp);
	assert(strcmp(temp, "W000") == false);

	initarray(temp, MAXSIZE);
	soundex("DeSmet", temp);
	assert(strcmp(temp, "D253") == false);

	initarray(temp, MAXSIZE);
	soundex("Gutierrez", temp);
	assert(strcmp(temp, "G362") == false);

	initarray(temp, MAXSIZE);
	soundex("Pfister", temp);
	assert(strcmp(temp, "P236") == false);

	initarray(temp, MAXSIZE);
	soundex("Jackson", temp);
	assert(strcmp(temp, "J250") == false);

	initarray(temp, MAXSIZE);
	soundex("Tymczak", temp);
	assert(strcmp(temp, "T522") == false);

	initarray(temp, MAXSIZE);
	soundex("Ashcraft", temp);
	assert(strcmp(temp, "A261") == false);
}
