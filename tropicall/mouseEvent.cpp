#include <SDL.h>
#include "settings.h"
#include "utils.h"
#include "drawingMethods.h"
#include "mouseEvent.h"
#include "toolbox.h"

void MOUSE_EVENTSs::mouseMotion(SDL_Renderer* renderer, SDL_Event event)
{
    if (SETTINGS_H::drawing) {
        SDL_SetRenderDrawColor(renderer, SETTINGS_H::drawR, SETTINGS_H::drawG, SETTINGS_H::drawB, SETTINGS_H::drawA);
        int dx = event.motion.x - SETTINGS_H::prevX;
        int dy = event.motion.y - SETTINGS_H::prevY;
        int steps = SDL_max(SDL_abs(dx), SDL_abs(dy));
        float stepX = (float)dx / steps;
        float stepY = (float)dy / steps;
        for (int i = 0; i < steps; ++i) {
            SDL_RenderDrawPoint(renderer, SETTINGS_H::prevX + stepX * i, SETTINGS_H::prevY + stepY * i);
            for (int j = -SETTINGS_H::radius; j <= SETTINGS_H::radius; ++j) {
                for (int k = -SETTINGS_H::radius; k <= SETTINGS_H::radius; ++k) {
                    if (j * j + k * k <= SETTINGS_H::radius * SETTINGS_H::radius) {
                        SDL_RenderDrawPoint(renderer, SETTINGS_H::prevX + stepX * i + j, SETTINGS_H::prevY + stepY * i + k);
                    }
                }
            }
        }
        SDL_RenderPresent(renderer);
        SETTINGS_H::prevX = event.motion.x;
        SETTINGS_H::prevY = event.motion.y;
    }
    toolBoXx::toolBoxFunc("MM", event);
}
void MOUSE_EVENTSs::MouseButtonDown(SDL_Renderer* renderer, SDL_Event event)
{
    if (event.button.button == SDL_BUTTON_LEFT) {
        toolBoXx::toolBoxFunc("MBD", event);
        UTILSs::LOG("SDL_MOUSEBUTTONDOWN->SDL_BUTTON_LEFT");
        SETTINGS_H::drawing = 1;
        UTILSs::LOG("DRAWING->1");
        SETTINGS_H::prevX = event.button.x;
        SETTINGS_H::prevY = event.button.y;
        SDL_SetRenderDrawColor(renderer, SETTINGS_H::drawR, SETTINGS_H::drawG, SETTINGS_H::drawB, SETTINGS_H::drawA);
        for (int j = -SETTINGS_H::radius; j <= SETTINGS_H::radius; ++j) {
            for (int k = -SETTINGS_H::radius; k <= SETTINGS_H::radius; ++k) {
                if (j * j + k * k <= SETTINGS_H::radius * SETTINGS_H::radius) {
                    SDL_RenderDrawPoint(renderer, SETTINGS_H::prevX + j, SETTINGS_H::prevY + k);
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
    else if (event.button.button == SDL_BUTTON_RIGHT) {
        UTILSs::LOG("SDL_MOUSEBUTTONDOWN->SDL_BUTTON_RIGHT");
        UTILSs::ClearScreen(renderer);
        UTILSs::LOG("SCREEN CLEARED.");
    }
}
