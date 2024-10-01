#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>

#define GRID_SIZE 20
#define MINES 100
#define RED  "\x1B[31m"
#define NRM  "\x1B[0m"

int calcmines(int x, int y, char grid[GRID_SIZE][GRID_SIZE], char c);
void random_initialise_grid(int mines, char grid[GRID_SIZE][GRID_SIZE]);
bool rule1(int known_mines, char board[GRID_SIZE][GRID_SIZE]);
bool rule2(int* mines, char board[GRID_SIZE][GRID_SIZE]);
void randomclick(char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]);
void weightedclick(char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]);
bool span(char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]);
bool win(char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]);
void printboard(char grid[GRID_SIZE][GRID_SIZE]);

int main() {
    char grid[GRID_SIZE][GRID_SIZE] = { 0 };
    srand(time(NULL));
    random_initialise_grid(MINES, grid);
   // printboard(grid);

    char board[GRID_SIZE][GRID_SIZE] = { 0 };

    int mines = 0;
    int clicks = 0;
    while (!win(grid, board)) {
        weightedclick(grid, board);
        bool flag0 = false;
        bool flag1 = false;
        bool flag2 = false;
        do{
            if (flag0 = span(grid, board)) {
                printboard(board);
                Sleep(500);
            }
            if (flag2 = rule2(&mines, board)) {
                printboard(board);
                Sleep(500);
            }
            if (flag1 = rule1(mines, board)) {
                printboard(board);
                Sleep(500);
            }
        } while (flag0 || flag1 || flag2);
    }
    printf("you win!\n");
}


void randomclick(char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]) {
    int x, y;
    while (board[x = rand() % GRID_SIZE][y = rand() % GRID_SIZE] != '\0');
    if (grid[x][y] == 'x') {
        printf("you click a mine, game over.\n");
        exit(1);
    }
    else if ('0' <= grid[x][y] && grid[x][y] <= '8') {
        board[x][y] = grid[x][y];
    }
    else {
        printf("something went wrong.\n");
    }
    //printf("x=%d,y=%d,grid[x][y]=%c\n", x, y, grid[x][y]);
}

void weightedclick(char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]) {
    int x, y;
    int weight = 8 * 8 + 1; // the highest possible weight plus one
    int temp = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            // calc weight
            if (board[i][j] == '\0') {
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        if (!(k == 0 && l == 0) && 0 <= i + k && i + k <= GRID_SIZE - 1 \
                            && 0 <= j + l && j + l <= GRID_SIZE - 1) {
                            if (board[i + k][j + l] == 'x') {
                                temp += 8;
                            }
                            else if ('0' <= board[i + k][j + l] && board[i + k][j + l] <= '9') {
                                temp += board[i + k][j + l] - '0';
                            }
                        }
                    }
                }
                if (temp < weight) {
                    weight = temp;
                    x = i;
                    y = j;
                }
                temp = 0;
            }
        }
    }

    if (grid[x][y] == 'x') {
        printf("you click a mine, game over.\n");
        exit(1);
    }
    else if ('0' <= grid[x][y] && grid[x][y] <= '8') {
        board[x][y] = grid[x][y];
    }
    else {
        printf("something went wrong. unexpected cell\n");
    }
    //printf("x=%d,y=%d,grid[x][y]=%c,weight=%d\n", x, y, grid[x][y], weight);
}

bool rule1(int known_mines, char board[GRID_SIZE][GRID_SIZE]) {
    bool flag = false;
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (board[y][x]=='\0' && known_mines == MINES) {
                board[y][x] = (char)(calcmines(x, y, board, 'x') + '0');
                flag = true;
            }
        }
    }
    return flag;
}

bool rule2(int* mines, char board[GRID_SIZE][GRID_SIZE]) {
    int count = 0;
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if ('0' <= board[y][x] && board[y][x] <= '8') {
                int unknown = calcmines(x, y, board, '\0');
                int known_mines = calcmines(x, y, board, 'x');
                if (board[x][y] - '0' == unknown + known_mines && unknown > 0) {
                    for (int j = -1; j <= 1; j++) {
                        for (int i = -1; i <= 1; i++) {
                            if (!(i == 0 && j == 0) && 0 <= x + i && x + i <= GRID_SIZE - 1 \
                                && 0 <= y + j && y + j <= GRID_SIZE - 1 && board[y + j][x + i] == '\0') {
                                board[y + j][x + i] = 'x';
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }
    *mines += count;
    return count > 0;
}

bool span(char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]) {
    bool flag = false;
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (board[y][x] == calcmines(x, y, grid, 'x') + '0'){
                for (int j = -1; j <= 1; j++) {
                    for (int i = -1; i <= 1; i++) {
                        if (!(i == 0 && j == 0) && 0 <= x + i && x + i <= GRID_SIZE - 1 \
                            && 0 <= y + j && y + j <= GRID_SIZE - 1 && board[y + j][x + i] == '\0') {
                            board[y + j][x + i] = grid[y + j][x + i];
                            flag = true;
                        }
                    }
                }
            }
        }
    }
    return flag;
}

void random_initialise_grid(int mines, char grid[GRID_SIZE][GRID_SIZE]) {
    int x, y;
    while (mines > 0) {
        x = rand() % GRID_SIZE;
        y = rand() % GRID_SIZE;
        if (grid[y][x] != 'x') {
            grid[y][x] = 'x';
            mines--;
        }
    }
    for (int j = 0; j < GRID_SIZE; j++) {
        for (int i = 0; i < GRID_SIZE; i++) {
            if (grid[j][i] != 'x') {
                grid[j][i] = calcmines(i, j, grid, 'x') + '0';
            }
        }
    }
}

int calcmines(int x, int y, char grid[GRID_SIZE][GRID_SIZE], char c) {
    int count = 0;
    for (int j = -1; j <= 1; j++) {
        for (int i = -1; i <= 1; i++) {
            if (!(i == 0 && j == 0) && 0 <= x + i && x + i <= GRID_SIZE - 1 \
                && 0 <= y + j && y + j <= GRID_SIZE - 1 && grid[y+j][x+i] == c) {
                count++;
            }
        }
    }
    return count;
}

bool win(char grid[GRID_SIZE][GRID_SIZE], char board[GRID_SIZE][GRID_SIZE]) {
    for (int j = 0; j < GRID_SIZE; j++) {
        for (int i = 0; i < GRID_SIZE; i++) {
            if (grid[j][i] != board[j][i]) {
                return false;
            }
        }
    }
    return true;
}

void printboard(char grid[GRID_SIZE][GRID_SIZE]) {
    printf("\033[H\033[J");
    for (int j = 0; j < GRID_SIZE; j++) {
        for (int i = 0; i < GRID_SIZE; i++) {
            if (grid[j][i] == 'x') {
                printf("%s%c ", RED, 'x');
            }
            else if (grid[j][i] == '\0') {
                printf("%s. ", NRM);
            }
            else {
                printf("%s%c ", NRM, grid[j][i]);
            }
        }
        printf("%s\n", NRM);
    }
    printf("%s\n", NRM);
}
