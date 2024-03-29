#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include "settings.h"

bool isMouseHover(int mouseX, int mouseY, int rectX, int rectY, int rectW, int rectH) {
    SDL_Rect rect;
    rect.x = rectX;
    rect.y = rectY;
    rect.h = rectH;
    rect.w = rectW;
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
        mouseY >= rect.y && mouseY <= rect.y + rect.h);
}

class toolBox
{
public:
    //TOOLBOX
    void static toolBoxMain(SDL_Renderer* renderer)
    {
        SDL_Rect toolBoxRect;
        toolBoxRect.x = SETTINGS_H::toolBoxX;
        toolBoxRect.y = SETTINGS_H::toolBoxY;
        toolBoxRect.w = SETTINGS_H::toolBoxW;
        toolBoxRect.h = SETTINGS_H::toolBoxH;
        SDL_SetRenderDrawColor(renderer, 74, 74, 74, 255);
        SDL_RenderFillRect(renderer, &toolBoxRect);
    };
    //COLOR 1
    void static color1(SDL_Renderer* renderer)
    {
        SDL_Rect color1;
        color1.x = SETTINGS_H::color1X;
        color1.y = SETTINGS_H::color1Y;
        color1.w = SETTINGS_H::color1W;
        color1.h = SETTINGS_H::color1H;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &color1);
    };
    void static color2(SDL_Renderer* renderer)
    {
        SDL_Rect color2;
        color2.x = SETTINGS_H::color2X;
        color2.y = SETTINGS_H::color2Y;
        color2.w = SETTINGS_H::color2W;
        color2.h = SETTINGS_H::color2H;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &color2);
    };
    void static color3(SDL_Renderer* renderer)
    {
        SDL_Rect color3;
        color3.x = SETTINGS_H::color3X;
        color3.y = SETTINGS_H::color3Y;
        color3.w = SETTINGS_H::color3W;
        color3.h = SETTINGS_H::color3H;
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &color3);
        SDL_RenderPresent(renderer);
    };
};

void toolBoxFunc(std::string MODE, SDL_Event event)
{
    if (MODE == "MBD")
    {
        if (SETTINGS_H::color1_isHovered)
        {
            SETTINGS_H::drawR = 255;
            SETTINGS_H::drawG = 0;
            SETTINGS_H::drawB = 0;
            SETTINGS_H::drawA = 255;
            return;
        }
        if (SETTINGS_H::color2_isHovered)
        {
            SETTINGS_H::drawR = 0;
            SETTINGS_H::drawG = 255;
            SETTINGS_H::drawB = 0;
            SETTINGS_H::drawA = 255;
            return;
        }
        if (SETTINGS_H::color3_isHovered)
        {
            SETTINGS_H::drawR = 0;
            SETTINGS_H::drawG = 0;
            SETTINGS_H::drawB = 255;
            SETTINGS_H::drawA = 255;
            return;
        }
    }
    if (MODE == "MM")
    {
        if (isMouseHover(event.motion.x, event.motion.y, SETTINGS_H::toolBoxX, SETTINGS_H::toolBoxY, SETTINGS_H::toolBoxW, SETTINGS_H::toolBoxH)) SETTINGS_H::toolBox_isHovered = true; else SETTINGS_H::toolBox_isHovered = false;
        if (isMouseHover(event.motion.x, event.motion.y, SETTINGS_H::color1X, SETTINGS_H::color1Y, SETTINGS_H::color1W, SETTINGS_H::color1H)) SETTINGS_H::color1_isHovered = true; else SETTINGS_H::color1_isHovered = false;
        if (isMouseHover(event.motion.x, event.motion.y, SETTINGS_H::color2X, SETTINGS_H::color2Y, SETTINGS_H::color2W, SETTINGS_H::color2H)) SETTINGS_H::color2_isHovered = true; else SETTINGS_H::color2_isHovered = false;
        if (isMouseHover(event.motion.x, event.motion.y, SETTINGS_H::color3X, SETTINGS_H::color3Y, SETTINGS_H::color3W, SETTINGS_H::color3H)) SETTINGS_H::color3_isHovered = true; else SETTINGS_H::color3_isHovered = false;
    }
}
void ClearScreen(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
void LOG(std::string message)
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
void mouseMotion(SDL_Renderer* renderer, SDL_Event event)
{
    if (drawing) {
        SDL_SetRenderDrawColor(renderer, SETTINGS_H::drawR, SETTINGS_H::drawG, SETTINGS_H::drawB, SETTINGS_H::drawA);
        int dx = event.motion.x - SETTINGS_H::prevX;
        int dy = event.motion.y - SETTINGS_H::prevY;
        int steps = SDL_max(SDL_abs(dx), SDL_abs(dy));
        float stepX = (float)dx / steps;
        float stepY = (float)dy / steps;
        for (int i = 0; i < steps; ++i) {
            SDL_RenderDrawPoint(renderer, prevX + stepX * i, prevY + stepY * i);
            for (int j = -SETTINGS_H::radius; j <= SETTINGS_H::radius; ++j) {
                for (int k = -SETTINGS_H::radius; k <= SETTINGS_H::radius; ++k) {
                    if (j * j + k * k <= SETTINGS_H::radius * SETTINGS_H::radius) {
                        SDL_RenderDrawPoint(renderer, prevX + stepX * i + j, prevY + stepY * i + k);
                    }
                }
            }
        }
        SDL_RenderPresent(renderer);
        prevX = event.motion.x;
        prevY = event.motion.y;
    }
    toolBoxFunc("MM", event);
}
void MouseButtonDown(SDL_Renderer* renderer, SDL_Event event)
{
    if (event.button.button == SDL_BUTTON_LEFT) {
        toolBoxFunc("MBD", event);
        LOG("SDL_MOUSEBUTTONDOWN->SDL_BUTTON_LEFT");
        drawing = 1;
        LOG("DRAWING->1");
        SETTINGS_H::prevX = event.button.x;
        SETTINGS_H::prevY = event.button.y;
        SDL_SetRenderDrawColor(renderer, SETTINGS_H::drawR, SETTINGS_H::drawG, SETTINGS_H::drawB, SETTINGS_H::drawA);
        for (int j = -SETTINGS_H::radius; j <= SETTINGS_H::radius; ++j) {
            for (int k = -SETTINGS_H::radius; k <= SETTINGS_H::radius; ++k) {
                if (j * j + k * k <= SETTINGS_H::radius * SETTINGS_H::radius) {
                    SDL_RenderDrawPoint(renderer, prevX + j, prevY + k);
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
    else if (event.button.button == SDL_BUTTON_RIGHT) {
        LOG("SDL_MOUSEBUTTONDOWN->SDL_BUTTON_RIGHT");
        ClearScreen(renderer);
        LOG("SCREEN CLEARED.");
    }
    else if (event.button.button == SDL_BUTTON_RIGHT) {
        SDL_SetRenderDrawColor(renderer, SETTINGS_H::drawR, SETTINGS_H::drawG, SETTINGS_H::drawB, SETTINGS_H::drawA);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}

int SDL_main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    LOG("SDL_INIT CALLED.");

    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
        fprintf(stderr, "SDL_GetDesktopDisplayMode Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow(SETTINGS_H::mainWindowTitle,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SETTINGS_H::mainWindowW, SETTINGS_H::mainWindowH,
        SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    LOG("WINDOW CREATED.");

    //FLAGS
    if (!SETTINGS_H::FullScreen)
    {
        SDL_SetWindowFullscreen(window, SETTINGS_H::FullScreenMode);
        LOG("FULLSCREEN MODE.");
    }
    //SDL_SetWindowAlwaysOnTop(window, SDL_TRUE);


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    LOG("SCREEN CLEARED.");
    ClearScreen(renderer);

    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                MouseButtonDown(renderer, event);
                break;
            case SDL_MOUSEBUTTONUP:
                LOG("SDL_MOUSEBUTTONDOWN->SDL_BUTTON_UP");
                if (event.button.button == SDL_BUTTON_LEFT) {
                    drawing = 0;
                    LOG("DRAWING->0");
                }
                break;
            case SDL_MOUSEMOTION:
                mouseMotion(renderer, event);
                break;
            case SDL_KEYDOWN:
                SETTINGS_H::radius += 1;
                break;
            }
        }

        toolBox::toolBoxMain(renderer);
        toolBox::color1(renderer);
        toolBox::color2(renderer);
        toolBox::color3(renderer);
    };

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

