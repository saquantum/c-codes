#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // For Sleep
#include <time.h>    // For time functions

#define ROWS 10
#define COLS 10

// Function to print the 2D array
void printArray(char array[ROWS][COLS]) {
    // Move the cursor to the top-left corner of the terminal
    printf("\033[H\033[J"); // Clear the screen
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", array[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char array[ROWS][COLS];

    // Initialize the array
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            array[i][j] = '.'; // Fill with dots
        }
    }

    // Simulate some dynamic changes in the array
    for (int iteration = 0; iteration < 20; iteration++) {
        // Randomly change some cells in the array
        int x = rand() % ROWS;
        int y = rand() % COLS;
        array[x][y] = (array[x][y] == '.') ? 'X' : '.'; // Toggle between 'X' and '.'

        // Print the updated array
        printArray(array);

        // Sleep for 500 milliseconds
        Sleep(500);
    }

    return 0;
}
