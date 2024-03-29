#include <SDL.h>
#include <SDL_syswm.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include "settings.h"

struct RGBA
{
    int r;
    int g;
    int b;
    int a;
};


bool isMouseHover(int mouseX, int mouseY, int rectX, int rectY, int rectW, int rectH) {
    SDL_Rect rect;
    rect.x = rectX;
    rect.y = rectY;
    rect.h = rectH;
    rect.w = rectW;
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
        mouseY >= rect.y && mouseY <= rect.y + rect.h);
}
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

class border
{
public:
    static void addBorder(SDL_Renderer* renderer, SDL_Rect rect, int radius, RGBA rgb)
    {
        SDL_Rect border;
        border.x = rect.x - (radius / 2);
        border.y = rect.y - (radius / 2);
        border.w = rect.w + radius;
        border.h = rect.h + radius;
        SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, rgb.a);
        SDL_RenderFillRect(renderer, &border);
    }
};
class toolBox
{
public:
    //TOOLBOX
    static void toolBoxMain(SDL_Renderer* renderer)
    {
        SDL_Rect toolBoxRect;
        toolBoxRect.x = SETTINGS_H::toolBoxX;
        toolBoxRect.y = SETTINGS_H::toolBoxY;
        toolBoxRect.w = SETTINGS_H::toolBoxW;
        toolBoxRect.h = SETTINGS_H::toolBoxH;
        if (SETTINGS_H::toolBox_isHovered)
        {
            border::addBorder(renderer, toolBoxRect, 10, RGBA(255, 0, 0, 255));
        }
        else {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            border::addBorder(renderer, toolBoxRect, 10, RGBA(0, 0, 0, 255));
        }
        SDL_SetRenderDrawColor(renderer, 74, 74, 74, 255); // Set alpha to 255 for full visibility
        SDL_RenderFillRect(renderer, &toolBoxRect);
    }

    static void color1(SDL_Renderer* renderer)
    {
        SDL_Rect color1;
        color1.x = SETTINGS_H::color1X;
        color1.y = SETTINGS_H::color1Y;
        color1.w = SETTINGS_H::color1W;
        color1.h = SETTINGS_H::color1H;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set alpha to 255 for full visibility
        SDL_RenderFillRect(renderer, &color1);
    }

    static void color2(SDL_Renderer* renderer)
    {
        SDL_Rect color2;
        color2.x = SETTINGS_H::color2X;
        color2.y = SETTINGS_H::color2Y;
        color2.w = SETTINGS_H::color2W;
        color2.h = SETTINGS_H::color2H;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set alpha to 255 for full visibility
        SDL_RenderFillRect(renderer, &color2);
    }

    static void color3(SDL_Renderer* renderer)
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

};


int SDL_main(int argc, char* argv[]) {
    LOG("SCREEN SIZED TO -> (" + std::to_string(SETTINGS_H::mainWindowW) + "," + std::to_string(SETTINGS_H::mainWindowH) + ")");
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
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
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

    SDL_Delay(16);

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
