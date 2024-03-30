#include <SDL.h>
#include <string>
#include "settings.h"

#ifndef BORDER
#define BORDER

namespace BORDEr
{
	void addDrawColorBorder(SDL_Renderer* renderer, SDL_Rect rect, int radius, bool clear);
	void addBorder(SDL_Renderer* renderer, SDL_Rect rect, int radius, RGBA rgb);
};
#endif

