#include "neillsdl2.h"
#include <stdio.h>
#include <stdlib.h>

#define SQUARE_SIZE 140  // Size of each square
#define START_X (WWIDTH / 2) -  SQUARE_SIZE/2  // Center the triangle horizontally
#define START_Y (WHEIGHT / 2) - (2 * SQUARE_SIZE) // Center the triangle vertically

void drawTriangleOfSquares(SDL_Simplewin* sw);

int main(void) {
    SDL_Simplewin sw;
    Neill_SDL_Init(&sw);

    drawTriangleOfSquares(&sw);

    Neill_SDL_UpdateScreen(&sw);
    SDL_Delay(5000);  // Keep the window open for 5 seconds

    SDL_Quit();
    atexit(SDL_Quit);
    return 0;
}

void drawTriangleOfSquares(SDL_Simplewin* sw) {
    int x = START_X;
    int y = START_Y;

    // Row 1: 1 square (shifted left by half a square)
    x = START_X;
    Neill_SDL_SetDrawColour(sw, 255, 0, 0);  // Red color
    SDL_Rect square1 = {x, y, SQUARE_SIZE, SQUARE_SIZE};
    SDL_RenderFillRect(sw->renderer, &square1);

    // Row 2: 2 squares (shifted left by half a square)
    y += SQUARE_SIZE;
    for (int i = 0; i < 2; i++) {
        x = START_X + i * SQUARE_SIZE - SQUARE_SIZE / 2;
        SDL_Rect square = {x, y, SQUARE_SIZE, SQUARE_SIZE};
        SDL_RenderFillRect(sw->renderer, &square);
    }

    // Row 3: 3 squares, with the center square as the "hole" (no shift needed)
    y += SQUARE_SIZE;
    for (int i = 0; i < 3; i++) {
        x = START_X + i * SQUARE_SIZE - SQUARE_SIZE;
        SDL_Rect square = {x, y, SQUARE_SIZE, SQUARE_SIZE};
        if (i == 1) {
            Neill_SDL_SetDrawColour(sw, 0, 0, 0);  // Black color for the "hole"
        } else {
            Neill_SDL_SetDrawColour(sw, 255, 0, 0);  // Red color
        }
        SDL_RenderFillRect(sw->renderer, &square);
    }

    // Row 4: 4 squares (no shift needed)
    y += SQUARE_SIZE;
    for (int i = 0; i < 4; i++) {
        x = START_X + i * SQUARE_SIZE - 3*SQUARE_SIZE / 2;
        Neill_SDL_SetDrawColour(sw, 255, 0, 0);  // Red color
        SDL_Rect square = {x, y, SQUARE_SIZE, SQUARE_SIZE};
        SDL_RenderFillRect(sw->renderer, &square);
    }
}
