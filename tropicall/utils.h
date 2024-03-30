#include <SDL.h>
#include <string>
#ifndef UTILS
#define UTILS

namespace UTILSs
{
	void ClearScreen(SDL_Renderer* renderer);
	void LOG(std::string message);
};
#endif