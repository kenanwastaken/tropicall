#include "dx/d3dx9.h"

#ifndef DIRECTX_IMPLEMENT
#define DIRECTX_IMPLEMENT

namespace DIRECTX
{
	void init_graphics(IDirect3DDevice9* d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer);
	void render_frame(IDirect3DDevice9* d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer);
}

#endif