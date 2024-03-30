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

//D3D9
#include <d3d9.h>
#include "dx/d3dx9.h"


//D3D9
IDirect3DDevice9* d3ddev;
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;

struct CUSTOMVERTEX { FLOAT X, Y, Z, RHW; DWORD COLOR; };
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

void init_graphics(void)
{
    // create the vertices using the CUSTOMVERTEX struct
    CUSTOMVERTEX vertices[] =
    {
        { 400.0f, 62.5f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 650.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 150.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
    };

    // create a vertex buffer interface called v_buffer
    d3ddev->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &v_buffer,
        NULL);

    VOID* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    v_buffer->Unlock();
}
void render_frame(void)
{
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    d3ddev->BeginScene();

    // select which vertex format we are using
    d3ddev->SetFVF(CUSTOMFVF);

    // select the vertex buffer to display
    d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

    // copy the vertex buffer to the back buffer
    d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

    d3ddev->EndScene();

    d3ddev->Present(NULL, NULL, NULL, NULL);
}

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
    };

    //SDL_Delay(16);

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
