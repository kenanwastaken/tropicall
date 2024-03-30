#include "triggers.h"

bool TRIGGERSs::isMouseHover(int mouseX, int mouseY, int rectX, int rectY, int rectW, int rectH) {
    SDL_Rect rect;
    rect.x = rectX;
    rect.y = rectY;
    rect.h = rectH;
    rect.w = rectW;
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
        mouseY >= rect.y && mouseY <= rect.y + rect.h);
};