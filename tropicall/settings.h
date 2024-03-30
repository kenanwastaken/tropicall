// data.h
#ifndef SETTINGS_H
#define SETTINGS_H
#include <windows.h>

struct RGBA
{
    int r;
    int g;
    int b;
    int a;
};


//MAIN
inline int running = 1;

//WINDOW
inline int mainWindowW = GetSystemMetrics(SM_CXSCREEN);
inline int mainWindowH = GetSystemMetrics(SM_CYSCREEN);
inline const char* mainWindowTitle = "tropicall";
inline bool FullScreen = false;
inline SDL_WindowFlags FullScreenMode = SDL_WINDOW_FULLSCREEN_DESKTOP;
inline SDL_bool WindowAlwaysOnTop = SDL_TRUE;

//DRAW
inline int drawR = 255;
inline int drawG = 0;
inline int drawB = 255;
inline int drawA = 255;
inline int radius = 1;
inline int drawing = 0;


//MOUSE
inline int prevX = 0;
inline int prevY = 0;

//TOOLBOX
inline int toolBoxX = 20;
inline int toolBoxY = (SETTINGS_H::mainWindowH / 2) - 300;
inline int toolBoxW = 80;
inline int toolBoxH = 600;
inline bool toolBox_isHovered;
inline RGBA toolBoxBorderRGBA(SETTINGS_H::drawR, SETTINGS_H::drawG, SETTINGS_H::drawB, SETTINGS_H::drawA);

//COLOR 1
inline int color1X = 30;
inline int color1Y = (SETTINGS_H::mainWindowH / 2) - 260;
inline int color1W = 25;
inline int color1H = 25;
inline bool color1_isHovered;

//COLOR 2
inline int color2X = 65;
inline int color2Y = (SETTINGS_H::mainWindowH / 2) - 260;
inline int color2W = 25;
inline int color2H = 25;
inline bool color2_isHovered;

//COLOR 3
inline int color3X = 65;
inline int color3Y = (SETTINGS_H::mainWindowH / 2) - 220;
inline int color3W = 25;
inline int color3H = 25;
inline bool color3_isHovered;


#endif
