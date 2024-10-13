#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define ROWS 20
#define COLUMNS 5
#define PLAYINGHEIGHT 6
#define ALPHASIZE 26

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

#define EMPTY '.'

typedef struct state {
   char board[ROWS][COLUMNS];
}state;

void solve(state* s);
bool win(state* s);
bool initialise(state* s, const char* str);
void str2board(state* s, const char* str);
bool tostring(const state* s, char* str);
int nonempty_line(const state* s);
bool matches(state* s);
bool dropblocks(state* s);
bool shiftarray(int shift, char arr[], int length, int pointer_dist);
bool three_in_a_sequence(int x, int y, state* s);
bool is_in_play_area(int x, int y);
bool is_in_board(int x, int y);
void printboard(state* s, int mode);
char* arr2str(char* a, int length);
void test(void);

int main(void)
{
   test();
}

void solve(state* s) {
	bool temp;
	while ((temp = dropblocks(s))) {
		printf("temp=%d\n", temp);
	};
	printf("temp=%d\n", temp);
	if (win(s)) {
		printf("You win!\n");
	}
	else {
		printf("Game set. Can't find any more to crush.\n");
	}
}

bool win(state* s) {
	for (int j = PLAYINGHEIGHT - 1; j >= 0; j--) {
		for (int i = 0; i < COLUMNS; i++) {
			if (s->board[j][i] != EMPTY) {
				return false;
			}
		}
	}
	return true;
}

bool initialise(state* s, const char* str){
    if(!str || !strlen(str) ){
        return false;
    }
// str is a file path: 
    FILE* fp=fopen(str,"r");
    if(fp){
        char buffer[ROWS*COLUMNS+1]={0};
        char c;
        int k=0;
        while((c=fgetc(fp))!=EOF){
            bool putinboard= ('A'<=c && c<='Z') || c==EMPTY;
            bool isauxchar= c==' '|| c=='\n' || c=='\r';
            bool isvalid= isupper || isauxchar;
            if(!isvalid){
                printf("invalid character detected in your input file.\n");
                return false;
            }
            if(putinboard){
                buffer[k]=c;
                k++;
            }
        }
        fclose(fp);
        str2board(s,buffer);
        return true;
    }
// str is a board string:
    if(strlen(str)%COLUMNS){
        return false;
    }
    int k=0;
    while(str[k]){
        bool putinboard= ('A'<=str[k] && str[k]<='Z') || str[k]==EMPTY;
        if (!putinboard){
            return false;
        }
        k++;
    }
    str2board(s,str);
    return true;
}

void str2board(state* s, const char* str){
    int l=strlen(str);
    if(l>ROWS*COLUMNS){
        printf("Your input string is too long and exceeds the maximum size of the board.\
         However I will proceed anyway but only part of the string will be put into the board.");
    }
    l--;
    for(int j=0;j<ROWS;j++){
        for(int i=COLUMNS-1;i>=0;i--){
            if(l>=0){
                s->board[j][i]=str[l];
                l--;
            }else{
                s->board[j][i]=EMPTY;
            }
        }
    }
}

bool tostring(const state* s, char* str){
    if(!s || !str){
        return false;
    }
    int line=nonempty_line(s);
    int k=0;
    for(;k<(line+1)*COLUMNS;k++){
        int j=line-k/COLUMNS;
        int i=k%COLUMNS;
        str[k]=s->board[j][i];
    }
    str[k]='\0';
    return true;
}

int nonempty_line(const state* s){
    for(int j=ROWS-1;j>=0;j--){
        int countempty=0;
        for(int i=0;i<COLUMNS;i++){
            countempty=s->board[j][i]==EMPTY?countempty+1:countempty;
        }
        
        if(countempty<COLUMNS){
            return j;
        }
    }
    return -1;
}

bool matches(state* s){
    if(!s){
        return false;
    }
    bool flag=false;
    bool temp[PLAYINGHEIGHT][COLUMNS] = { 0 };
	for (int j = PLAYINGHEIGHT - 1; j >= 0; j--) {
		for (int i = 0; i < COLUMNS; i++) {
			temp[j][i] = three_in_a_sequence(i, j, s);
		}
	}
    for (int j = PLAYINGHEIGHT - 1; j >= 0; j--) {
		for (int i = 0; i < COLUMNS; i++) {
		    if(temp[j][i]){
		        s->board[j][i]=EMPTY;
		        flag=true;    
		    }
		}
	}
    return flag;
}

bool dropblocks(state* s){
    if(!s){
        return false;
    }
    bool flag = false;
	for (int j = PLAYINGHEIGHT - 1; j >= 0; j--) {
		for (int i = 0; i < COLUMNS; i++) {
			if (s->board[j][i]==EMPTY) {
				if (!shiftarray(-1, &(s->board[j][i]), ROWS-j, COLUMNS)) {
					printf("Not enough heap memory!\n");
					exit(1);
				}
				else {
					flag = true;
				}
			}
		}
	}
	return flag;
}

bool shiftarray(int shift, char arr[], int length, int pointer_dist) {
	// discard out of bounds, and replace empty position with 0
	/* we are passing columns of 2d array to this function so we need to set
	   the pointer_dist to be the widths of that grid */
	char* temp = (char*)malloc(length * sizeof(char));
	if (temp == NULL) {
		return false;
	}
	for (int i = 0; i < length; i++) {
		temp[i] = arr[i * pointer_dist];
	}
	for (int i = 0; i < length; i++) {
		if (0 <= i - shift && i - shift < length) {
			arr[i * pointer_dist] = temp[i - shift];
		}
		else {
			arr[i * pointer_dist] = EMPTY;
		}
	}
	free(temp);
	return true;
}

/* this function is from my own 4.02.1_binarygrid code, 
i don't know if i need to cite this, anyway, now i've cited. */
bool three_in_a_sequence(int x, int y, state* s) {
	// return true if three in a sequence
	char diff[] = { 'x','y' };
	// choose which direction to be considered
	for (int c = 0; c < 2; c++) {
		int sx = diff[c] == 'x' ? 1 : 0;
		int sy = diff[c] == 'y' ? 1 : 0;
		for (int k = -2; k <= 0; k++) {
			// consider consecutive three
			int x1 = x + k * sx;
			int y1 = y + k * sy;
			int x2 = x + (k + 1) * sx;
			int y2 = y + (k + 1) * sy;
			int x3 = x + (k + 2) * sx;
			int y3 = y + (k + 2) * sy;
			if (is_in_play_area(x1, y1) && is_in_play_area(x3, y3)\
				&& s->board[y1][x1]!=EMPTY \
				&& s->board[y1][x1] == s->board[y2][x2]\
				&& s->board[y1][x1] == s->board[y3][x3]) {
				return true;
			}
		}
	}
	return false;
}

bool is_in_play_area(int x, int y) {
	return is_in_board(x,y) && y < PLAYINGHEIGHT;
}

bool is_in_board(int x, int y) {
	return (0 <= x) && (x < COLUMNS) && (0 <= y) && (y < ROWS);
}

void printboard(state* s, int mode) {
	// mode==0: print only the playing area
	// mode!=0: print all rows
	for (int j = mode == 0 ? PLAYINGHEIGHT - 1 : ROWS - 1; j >= 0; j--) {
		for (int i = 0; i < COLUMNS; i++) {
			printf("%s%2c", three_in_a_sequence(i, j, s) ? RED : NRM, s->board[j][i]);
		}
		printf("%s\n", NRM);
	}
	printf("%s\n", NRM);
}

char* arr2str(char* a, int length){ // must use with "free"!
    if(!a || length<0){
        return NULL;
    }
    
    char* out=(char*)malloc(sizeof(char)*(length+1));
    if(!out){
        return NULL;
    }
    for(int i=0;i<length;i++){
        out[i]=a[i];
    }
    out[length]='\0';
    return out;
}

void test(void){
   state s;
    
    initialise(&s, "...............");
    assert(nonempty_line(&s) == -1);

    initialise(&s, "...............ABCDE");
    assert(nonempty_line(&s) == 0);

    initialise(&s, "...............ABCDE....."); 
    assert(nonempty_line(&s) == 1);
    
    initialise(&s, "...............A.C.E.........."); 
    assert(nonempty_line(&s) == 2);
    
    char arr1[] = {'A', 'B', 'C', 'D', 'E'};
    assert(shiftarray(-1, arr1, 5, 1) == true);
    char* result1 = arr2str(arr1, 5);
    assert(strcmp(result1, "BCDE.") == 0);
    free(result1);

    // Test case 2: Shift right by 1, simple array
    char arr2[] = {'A', 'B', 'C', 'D', 'E'};
    assert(shiftarray(1, arr2, 5, 1) == true);
    char* result2 = arr2str(arr2, 5);
    assert(strcmp(result2, ".ABCD") == 0);
    free(result2);

    // Test case 3: No shift (shift = 0)
    char arr3[] = {'1', '2', '3', '4', '5'};
    assert(shiftarray(0, arr3, 5, 1) == true);
    char* result3 = arr2str(arr3, 5);
    assert(strcmp(result3, "12345") == 0);
    free(result3);

    // Test case 4: Shift left by more than length (should empty array)
    char arr4[] = {'1', '2', '3', '4', '5'};
    assert(shiftarray(-6, arr4, 5, 1) == true);
    char* result4 = arr2str(arr4, 5);
    assert(strcmp(result4, ".....") == 0);
    free(result4);

    // Test case 5: Shift right by more than length (should empty array)
    char arr5[] = {'1', '2', '3', '4', '5'};
    assert(shiftarray(6, arr5, 5, 1) == true);
    char* result5 = arr2str(arr5, 5);
    assert(strcmp(result5, ".....") == 0);
    free(result5);

    // Test case 6: Shift in a 2D array (pointer_dist > 1), column shift
    char board[5][5] = {
        {'A', 'B', 'C', 'D', 'E'},
        {'F', 'G', 'H', 'I', 'J'},
        {'K', 'L', 'M', 'N', 'O'},
        {'P', 'Q', 'R', 'S', 'T'},
        {'U', 'V', 'W', 'X', 'Y'}
    };
    // Shifting the first column of the board by 1 down (pointer_dist = 5)
    assert(shiftarray(1, &(board[0][0]), 5, 5) == true);
    char* result6 = arr2str((char*)board, 25); // Flatten 2D array into a string
    assert(strcmp(result6, ".BFKPUCGLQVDRHMWESINXTOJY") == 0); // Check expected result
    free(result6);
    
    s.board[0][0] = 'A'; s.board[0][1] = 'A'; s.board[0][2] = 'A'; s.board[0][3] = '.'; s.board[0][4] = '.';
    assert(three_in_a_sequence(0, 0, &s) == true); // Match starting at (0,0)
    assert(three_in_a_sequence(1, 0, &s) == true); // Match starting at (1,0)
    assert(three_in_a_sequence(2, 0, &s) == true); // Match starting at (2,0)
    assert(three_in_a_sequence(3, 0, &s) == false); // No match

    // Test case 2: Vertical match
    s.board[0][0] = 'B'; s.board[1][0] = 'B'; s.board[2][0] = 'B'; s.board[3][0] = '.'; s.board[4][0] = 'C';
    assert(three_in_a_sequence(0, 0, &s) == true); // Match starting at (0,0)
    assert(three_in_a_sequence(0, 1, &s) == true); // Match starting at (0,1)
    assert(three_in_a_sequence(0, 2, &s) == true); // Match starting at (0,2)
    assert(three_in_a_sequence(0, 3, &s) == false); // No match

    // Test case 3: Mixed characters with no matches
    s.board[0][0] = 'C'; s.board[0][1] = 'D'; s.board[0][2] = 'E'; s.board[0][3] = 'F'; s.board[0][4] = 'G';
    assert(three_in_a_sequence(0, 0, &s) == false); // No match

    // Test case 4: Edge case with dots
    s.board[0][0] = '.'; s.board[0][1] = '.'; s.board[0][2] = 'A'; s.board[0][3] = 'A'; s.board[0][4] = 'A';
    assert(three_in_a_sequence(2, 0, &s) == true); // Match starts at (2,0)
    assert(three_in_a_sequence(3, 0, &s) == false); // No match

    // Test case 5: Out of bounds check
    s.board[0][0] = 'A'; s.board[1][0] = 'A'; s.board[2][0] = 'A';
    assert(three_in_a_sequence(0, 3, &s) == false); // Out of bounds
    assert(three_in_a_sequence(3, 0, &s) == false); // Out of bounds

}
