#include <SDL.h>
#include <string>
#ifndef DRAWMETHODS
#define DRAWMETHODS

namespace DRAWMETHOD
{
	void drawDashLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int dashLength, int gapLength);
};
#endif