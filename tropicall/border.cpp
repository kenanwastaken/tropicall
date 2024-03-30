#include <SDL.h>
#include "settings.h"
#include "border.h"

void BORDEr::addDrawColorBorder(SDL_Renderer* renderer, SDL_Rect rect, int radius, bool clear)
{
    SDL_Rect border;
    border.x = rect.x - (radius / 2);
    border.y = rect.y - (radius / 2);
    border.w = rect.w + radius;
    border.h = rect.h + radius;
    if (clear)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &border);
        return;
    }
    SDL_SetRenderDrawColor(renderer, SETTINGS_H::drawR, SETTINGS_H::drawG, SETTINGS_H::drawB, SETTINGS_H::drawA);
    SDL_RenderFillRect(renderer, &border);
}
void BORDEr::addBorder(SDL_Renderer* renderer, SDL_Rect rect, int radius, RGBA rgb)
{
    SDL_Rect border;
    border.x = rect.x - (radius / 2);
    border.y = rect.y - (radius / 2);
    border.w = rect.w + radius;
    border.h = rect.h + radius;
    SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, rgb.a);
    SDL_RenderFillRect(renderer, &border);
}