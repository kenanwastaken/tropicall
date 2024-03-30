#include <SDL.h>
#include <string>
#include "toolbox.h"
#include "settings.h"
#include "triggers.h"
#include "border.h"

void toolBoXx::toolBoxMain(SDL_Renderer* renderer)
{
    SDL_Rect toolBoxRect;
    toolBoxRect.x = SETTINGS_H::toolBoxX;
    toolBoxRect.y = SETTINGS_H::toolBoxY;
    toolBoxRect.w = SETTINGS_H::toolBoxW;
    toolBoxRect.h = SETTINGS_H::toolBoxH;
    if (SETTINGS_H::toolBox_isHovered)
    {
        BORDEr::addDrawColorBorder(renderer, toolBoxRect, 10, false);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        BORDEr::addDrawColorBorder(renderer, toolBoxRect, 10, true);
    }
    SDL_SetRenderDrawColor(renderer, 74, 74, 74, 255);
    SDL_RenderFillRect(renderer, &toolBoxRect);
}
void toolBoXx::toolBoxFunc(std::string MODE, SDL_Event event)
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
        if (TRIGGERSs::isMouseHover(event.motion.x, event.motion.y, SETTINGS_H::toolBoxX, SETTINGS_H::toolBoxY, SETTINGS_H::toolBoxW, SETTINGS_H::toolBoxH)) SETTINGS_H::toolBox_isHovered = true; else SETTINGS_H::toolBox_isHovered = false;
        if (TRIGGERSs::isMouseHover(event.motion.x, event.motion.y, SETTINGS_H::color1X, SETTINGS_H::color1Y, SETTINGS_H::color1W, SETTINGS_H::color1H)) SETTINGS_H::color1_isHovered = true; else SETTINGS_H::color1_isHovered = false;
        if (TRIGGERSs::isMouseHover(event.motion.x, event.motion.y, SETTINGS_H::color2X, SETTINGS_H::color2Y, SETTINGS_H::color2W, SETTINGS_H::color2H)) SETTINGS_H::color2_isHovered = true; else SETTINGS_H::color2_isHovered = false;
        if (TRIGGERSs::isMouseHover(event.motion.x, event.motion.y, SETTINGS_H::color3X, SETTINGS_H::color3Y, SETTINGS_H::color3W, SETTINGS_H::color3H)) SETTINGS_H::color3_isHovered = true; else SETTINGS_H::color3_isHovered = false;
    }
}