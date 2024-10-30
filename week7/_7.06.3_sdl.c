#include "neillsdl2.h"
#include <math.h>

void drawCircleOfCircles(SDL_Simplewin* sw, int centerX, int centerY, int n, int bigRadius, int smallRadius, double lineAngle);

int main(void) {
    SDL_Simplewin sw;
    Neill_SDL_Init(&sw);

    int numCircles = 2;            // Try 2 circles to use the line angle adjustment
    int bigRadius = 100;
    int smallRadius = 10;
    double lineAngle = M_PI / 4;   // 45 degrees, for example

    drawCircleOfCircles(&sw, WWIDTH / 2, WHEIGHT / 2, numCircles, bigRadius, smallRadius, lineAngle);

    Neill_SDL_UpdateScreen(&sw);
    SDL_Delay(5000);  // Keep the window open for 5 seconds

    SDL_Quit();
    atexit(SDL_Quit);
    return 0;
}

void drawCircleOfCircles(SDL_Simplewin* sw, int centerX, int centerY, int n, int bigRadius, int smallRadius, double lineAngle) {
    double angleStep, startAngle;

    if (n == 2) {
        // For two circles, use the specified line angle
        angleStep = M_PI;  // 180 degrees to place two circles on opposite sides
        startAngle = lineAngle - M_PI / 2;  // Offset by 90 degrees to align line with lineAngle
    } else {
        // Regular circular arrangement for n > 2
        angleStep = 2 * M_PI / n;
        startAngle = M_PI / 2 - M_PI / n;  // Offset angle for bottom alignment
    }

    for (int i = 0; i < n; i++) {
        double angle = startAngle + i * angleStep;

        // Calculate the position of each small circle
        int smallCenterX = centerX + (int)(bigRadius * cos(angle));
        int smallCenterY = centerY + (int)(bigRadius * sin(angle));

        // Draw the small circle
        Neill_SDL_SetDrawColour(sw, 255, 0, 0);  // Red color
        SDL_RenderDrawCircle(sw->renderer, smallCenterX, smallCenterY, smallRadius);
    }
}
