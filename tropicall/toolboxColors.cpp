#include <SDL.h>
#include "toolboxColors.h"

void toolboxColors::color1(SDL_Renderer* renderer)
{
    SDL_Rect color1;
    color1.x = SETTINGS_H::color1X;
    color1.y = SETTINGS_H::color1Y;
    color1.w = SETTINGS_H::color1W;
    color1.h = SETTINGS_H::color1H;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set alpha to 255 for full visibility
    SDL_RenderFillRect(renderer, &color1);
}
void toolboxColors::color2(SDL_Renderer* renderer)
{
    SDL_Rect color2;
    color2.x = SETTINGS_H::color2X;
    color2.y = SETTINGS_H::color2Y;
    color2.w = SETTINGS_H::color2W;
    color2.h = SETTINGS_H::color2H;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set alpha to 255 for full visibility
    SDL_RenderFillRect(renderer, &color2);
}
void toolboxColors::color3(SDL_Renderer* renderer)
{
    SDL_Rect color3;
    color3.x = SETTINGS_H::color3X;
    color3.y = SETTINGS_H::color3Y;
    color3.w = SETTINGS_H::color3W;
    color3.h = SETTINGS_H::color3H;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Set alpha to 255 for full visibility
    SDL_RenderFillRect(renderer, &color3);
    SDL_RenderPresent(renderer); // Only call this if you want color3 to be immediately visible
}