// data.h
#ifndef SETTINGS_H
#define SETTINGS_H
#include <windows.h>

//MAIN
extern int running = 1;

//WINDOW
extern int mainWindowW = GetSystemMetrics(SM_CXSCREEN);
extern int mainWindowH = GetSystemMetrics(SM_CYSCREEN);
extern const char* mainWindowTitle = "tropicall";
extern bool FullScreen = false;
extern SDL_WindowFlags FullScreenMode = SDL_WINDOW_FULLSCREEN_DESKTOP;
extern SDL_bool WindowAlwaysOnTop = SDL_TRUE;

//DRAW
extern int drawR = 255;
extern int drawG = 0;
extern int drawB = 255;
extern int drawA = 255;
extern int radius = 1;
extern int drawing = 0;


//MOUSE
extern int prevX = 0;
extern int prevY = 0;

//TOOLBOX
extern int toolBoxX = 20;
extern int toolBoxY = (SETTINGS_H::mainWindowH / 2) - 300;
extern int toolBoxW = 80;
extern int toolBoxH = 600;
bool toolBox_isHovered;

//COLOR 1
extern int color1X = 30;
extern int color1Y = (SETTINGS_H::mainWindowH / 2) - 260;
extern int color1W = 25;
extern int color1H = 25;
bool color1_isHovered;

//COLOR 2
extern int color2X = 65;
extern int color2Y = (SETTINGS_H::mainWindowH / 2) - 260;
extern int color2W = 25;
extern int color2H = 25;
bool color2_isHovered;

//COLOR 3
extern int color3X = 65;
extern int color3Y = (SETTINGS_H::mainWindowH / 2) - 220;
extern int color3W = 25;
extern int color3H = 25;
bool color3_isHovered;


#endif
