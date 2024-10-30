#include "neillsdl2.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>

void drawcircles(SDL_Simplewin* sw, int centerX, int centerY, int prime, int bigRadius, int smallRadius, double lineangle);

int main(void) {
    SDL_Simplewin sw;
    Neill_SDL_Init(&sw);

    int prime = 7;            
    int bigR = 150;
    int smallR = 10;
    double lineangle = M_PI / 4;

    // we consider 4 as a prime when plotting!    
    
    drawcircles(&sw, WWIDTH / 2, WHEIGHT / 2, prime, bigR, smallR, lineangle);

    Neill_SDL_UpdateScreen(&sw);
    SDL_Delay(5000);
    SDL_Quit();
    atexit(SDL_Quit);
    return 0;
}

void drawcircles(SDL_Simplewin* sw, int centerX, int centerY, int prime, int bigR, int smallR, double lineangle) {
    double anglediff = 2 * M_PI / prime;
    double angle0;
    // if prime=2, the line angle is considered.
    if (prime == 2) {
        angle0 = lineangle;
    } else {
        // this formula assures that the bottom edge is parallel to the window
        angle0 = M_PI / 2 - M_PI / prime; 
    }

    for (int i = 0; i < prime; i++) {
        double angle = angle0 + i * anglediff;
        // using polar coordinates, x=x0+cos(θ), y=y0+sin(θ).
        int smallCenterX = centerX + (int)(bigR * cos(angle));
        int smallCenterY = centerY + (int)(bigR * sin(angle));
        Neill_SDL_SetDrawColour(sw,255,255,0);
        Neill_SDL_RenderFillCircle(sw->renderer, smallCenterX, smallCenterY, smallR);
    }
}
