#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

#define WALL '#'
#define PATH '.'

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"
#define NRM  "\x1B[0m"

void test();
bool reachedExit(int k, char* path, int height, int width);
void findPath(const char* maze, int start, char* path, int height, int width);
int mazeEntrance(const char* maze, int height, int width);
char* maze2String(const char* maze, int height, int width);
char* string2Maze(const char* str, int height, int width);
void printMaze(const char* maze, int height, int width);
void printPath(const char* path, int height, int width);

int main() {
	test();
}

bool reachedExit(int k, char* path, int height, int width) {
	int count = 0;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			count = path[i + j * width] == PATH?count + 1:count;
		}
	}
	bool boundary = (0 <= k && k < width) || ((height - 1) * width <= k && k < height * width) || k % width == 0 || k % width == width - 1;
	return count > 1 && boundary;
}

void findPath(const char* maze, int start, char* path, int height, int width) {
	path[start] = PATH;
	if (reachedExit(start, path, height, width)) {
		printPath(path, height, width);
		path[start] = 0;
		return;
	}
	int x0 = start % width;
	int y0 = start / width;
	char directions[] = { 'u','r','d','l' };
	for (int i = 0; i < 4; i++) {
		int x = x0;
		int y = y0;
		char c = directions[i];
		x = (c == 'r') ? x + 1 : (c == 'l') ? x - 1 : x;
		y = (c == 'u') ? y - 1 : (c == 'd') ? y + 1 : y;
		int nextIndex = x + y * width;
		if (x >= 0 && x < width && y >= 0 && y < height && maze[nextIndex] == PATH && path[nextIndex] != PATH) {
			findPath(maze, nextIndex, path, height, width);;
		}
	}
	path[start] = 0;
}

int mazeEntrance(const char* maze, int height, int width) {
	int lim = height < width ? height : width;
	for (int k = 0; k < lim; k++) {
		if (maze[k] == PATH) {
			return k;
		}
		else if (maze[k * width] == PATH) {
			return k * width;
		}
	}
	return -1;
}

char* maze2String(const char* maze, int height, int width) {
	char* str = (char*)calloc(height*width+1,sizeof(char));
	assert(str);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			str[i + j * width] = maze[i + j * width];
		}
	}
	return str;
}

char* string2Maze(const char* str, int height, int width) {
	char* maze= (char*)calloc(height * width, sizeof(char));
	assert(maze);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			maze[i + j * width] = str[i + j * width];
		}
	}
	return maze;
}

void printMaze(const char* maze, int height, int width) {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			printf("%c ", maze[i + j * width]);
		}
		printf("\n");
	}
}

void printPath(const char* path, int height, int width) {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (path[i + j * width] == PATH) {
				printf("%s%c ",GRN, path[i + j * width]);
			}
			else {
				printf("%sx ",RED);
			}
		}
		printf("\n");
	}
}

void test() {
	char* str = "###########.#......#..#.#.##.##.#.####.##.#....#.##.#.####.##.#....#.##.####.#.##......#..##########";
	int height = 10;
	int width = 10;
	char* M=string2Maze(str, height, width);
	printMaze(M, height, width);
	printf("entrance = %d\n",mazeEntrance(M, height, width));
	char* path = calloc(height * width, sizeof(char));
	findPath(M, mazeEntrance(M, height, width),path,height,width);
	free(path);
	free(M);
}
