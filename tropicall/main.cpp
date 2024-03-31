//SDL2
#include <SDL.h>
#include <SDL_syswm.h>

//CLASSICS
#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>

//OWN FILES
#include "settings.h"
#include "border.h"
#include "drawingMethods.h"
#include "mouseEvent.h"
#include "toolbox.h"
#include "toolboxColors.h"
#include "triggers.h"
#include "utils.h"
#include "drawingMethods.h"



int SDL_main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    UTILSs::LOG("SCREEN SIZED TO -> (" + std::to_string(SETTINGS_H::mainWindowW) + "," + std::to_string(SETTINGS_H::mainWindowH) + ")");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    UTILSs::LOG("SDL_INIT CALLED.");

    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
        fprintf(stderr, "SDL_GetDesktopDisplayMode Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    window = SDL_CreateWindow(SETTINGS_H::mainWindowTitle,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SETTINGS_H::mainWindowW, SETTINGS_H::mainWindowH,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    UTILSs::LOG("WINDOW CREATED.");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    UTILSs::LOG("SCREEN CLEARED.");
    UTILSs::ClearScreen(renderer);

    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                MOUSE_EVENTSs::MouseButtonDown(renderer, event);
                break;
            case SDL_MOUSEBUTTONUP:
                UTILSs::LOG("SDL_MOUSEBUTTONDOWN->SDL_BUTTON_UP");
                if (event.button.button == SDL_BUTTON_LEFT) {
                    SETTINGS_H::drawing = 0;
                    UTILSs::LOG("DRAWING->0");
                }
                break;
            case SDL_MOUSEMOTION:
                MOUSE_EVENTSs::mouseMotion(renderer, event);
                break;
            }
        }

        toolBoXx::toolBoxMain(renderer);
        toolboxColors::color1(renderer);
        toolboxColors::color2(renderer);
        toolboxColors::color3(renderer);
        toolboxColors::color4(renderer);
    };

    //SDL_Delay(16);

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
