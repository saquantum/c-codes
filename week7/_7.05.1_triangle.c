#include "neillsdl2.h"
#include <stdio.h>
#include <stdlib.h>

#define SQUARE_SIZE 4  // Size of each square

void recursion(SDL_Simplewin* sw, int centerX, int centerY, int size);
void drawTriangleOfSquares(SDL_Simplewin* sw, int centerX, int centerY, int size);

int main(void) {
    SDL_Simplewin sw;
    Neill_SDL_Init(&sw);
    int size=4*64;
    recursion(&sw,(WWIDTH / 2),(WHEIGHT / 2),size);

    Neill_SDL_UpdateScreen(&sw);
    SDL_Delay(5000);  // Keep the window open for 5 seconds

    SDL_Quit();
    atexit(SDL_Quit);
    return 0;
}

void recursion(SDL_Simplewin* sw, int centerX, int centerY, int size){
    if(size<=1){
        drawTriangleOfSquares(sw,centerX,centerY,size);
        return;
    }
    size/=2;
    recursion(sw,centerX,centerY-size/2,size);
    recursion(sw,centerX-size/2,centerY+size/2,size);
    recursion(sw,centerX+size/2,centerY+size/2,size);
}

void drawTriangleOfSquares(SDL_Simplewin* sw, int centerX, int centerY, int size) {
    // Row 1: 1 square (shifted left by half a square)
    int y=centerY;
    int x = centerX;
    Neill_SDL_SetDrawColour(sw, 255, 0, 0);  // Red color
    SDL_Rect square1 = {x, y, size, size};
    SDL_RenderFillRect(sw->renderer, &square1);

    // Row 2: 2 squares (shifted left by half a square)
    y += size;
    for (int i = 0; i < 2; i++) {
        x = centerX + i * size - size / 2;
        SDL_Rect square = {x, y, size, size};
        SDL_RenderFillRect(sw->renderer, &square);
    }

    // Row 3: 3 squares, with the center square as the "hole" (no shift needed)
    y += size;
    for (int i = 0; i < 3; i++) {
        x = centerX + i * size - size;
        SDL_Rect square = {x, y, size, size};
        if (i == 1) {
            Neill_SDL_SetDrawColour(sw, 0, 0, 0);  // Black color for the "hole"
        } else {
            Neill_SDL_SetDrawColour(sw, 255, 0, 0);  // Red color
        }
        SDL_RenderFillRect(sw->renderer, &square);
    }

    // Row 4: 4 squares (no shift needed)
    y += size;
    for (int i = 0; i < 4; i++) {
        x = centerX + i * size - 3*size / 2;
        Neill_SDL_SetDrawColour(sw, 255, 0, 0);  // Red color
        SDL_Rect square = {x, y, size, size};
        SDL_RenderFillRect(sw->renderer, &square);
    }
}
