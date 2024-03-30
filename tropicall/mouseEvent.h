#ifndef MOUSE_EVENTS
#define MOUSE_EVENTS

#include <SDL.h>

namespace MOUSE_EVENTSs
{
    void MouseButtonDown(SDL_Renderer* renderer, SDL_Event event);
    void mouseMotion(SDL_Renderer* renderer, SDL_Event event);
};

#endif
