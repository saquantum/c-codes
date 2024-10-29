#include "neillsdl2.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>

#define RECTS 81

void recursion(SDL_Simplewin* sw, int centerX, int centerY, int size);
void drawSquareWithHole(SDL_Simplewin* sw, int centerX, int centerY, int size);

int main(void){
    SDL_Simplewin sw;

    Neill_SDL_Init(&sw);
    do{

        SDL_Delay(MILLISECONDDELAY);
        
        int cx=WWIDTH/2-3*RECTS/2;
        int cy=WHEIGHT/2-3*RECTS/2;
        recursion(&sw,cx,cy,RECTS);
        
        Neill_SDL_UpdateScreen(&sw);
        Neill_SDL_Events(&sw);
    }while(!sw.finished);
    /* Clear up graphics subsystems */
    SDL_Quit();
    atexit(SDL_Quit);

   return 0;
}

void recursion(SDL_Simplewin* sw, int centerX, int centerY, int size){
    drawSquareWithHole(sw,centerX,centerY,size);
    if(size/3<=1){
        return;
    }
    recursion(sw,centerX,centerY,size/3);
    recursion(sw,centerX+size,centerY,size/3);
    recursion(sw,centerX+2*size,centerY,size/3);
        
    recursion(sw,centerX,centerY+size,size/3);
    recursion(sw,centerX+2*size,centerY+size,size/3);
        
    recursion(sw,centerX,centerY+2*size,size/3);
    recursion(sw,centerX+size,centerY+2*size,size/3);
    recursion(sw,centerX+2*size,centerY+2*size,size/3);
}

void drawSquareWithHole(SDL_Simplewin* sw, int centerX, int centerY, int size){
    int bigside=3*size;
    SDL_Rect big={centerX, centerY, bigside, bigside};
    Neill_SDL_SetDrawColour(sw,255,0,0);
    SDL_RenderFillRect(sw->renderer, &big);    
    int smallside=size;
    SDL_Rect small={centerX+smallside, centerY+smallside, smallside, smallside};
    Neill_SDL_SetDrawColour(sw,0,0,0);
    SDL_RenderFillRect(sw->renderer, &small);
}
