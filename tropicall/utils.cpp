#include <SDL.h>
#include <iostream>
#include <Windows.h>
#include "utils.h"

void UTILSs::LOG(std::string message)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << "[";
    SetConsoleTextAttribute(hConsole, 11);
    std::cout << "DEV";
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << "] ";
    SetConsoleTextAttribute(hConsole, 9);
    std::cout << "> ";
    SetConsoleTextAttribute(hConsole, 15);
    std::cout << message << std::endl;
}
void UTILSs::ClearScreen(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}