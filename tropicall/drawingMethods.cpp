#include <SDL.h>
#include "drawingMethods.h"

void  DRAWMETHOD::drawDashLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int dashLength, int gapLength)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float distance = sqrt(dx * dx + dy * dy);

    float dirX = dx / distance;
    float dirY = dy / distance;

    float dashRemaining = dashLength;
    float gapRemaining = gapLength;

    float x = x1;
    float y = y1;
    while (distance >= 0.0f) {
        if (dashRemaining > 0.0f) {
            SDL_RenderDrawPoint(renderer, static_cast<int>(x), static_cast<int>(y));
            dashRemaining -= 1.0f;
            distance -= 1.0f;
            x += dirX;
            y += dirY;
        }
        else {
            gapRemaining -= 1.0f;
            distance -= 1.0f;
            x += dirX;
            y += dirY;
            if (gapRemaining <= 0.0f) {
                dashRemaining = dashLength;
                gapRemaining = gapLength;
            }
        }
    }
}
