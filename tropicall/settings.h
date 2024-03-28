// data.h
#ifndef SETTINGS_H
#define SETTINGS_H

//MAIN
extern int running = 1;

//WINDOW
extern int mainWindowW = 2560;
extern int mainWindowH = 1440;
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

#endif
