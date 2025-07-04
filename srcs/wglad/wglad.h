#pragma once

#define WIN32_LEAN_AND_MEAN 1
#pragma comment(lib, "opengl32")

#pragma warning(disable:4005)

#include <wglad/wgl.h>

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

namespace wglad {

	/// @brief load glad function pointers and extensions
	void 	load_gl_extension();

	/// @brief create the resouce of Graphics Device
	/// @param hwnd specifies the window handle
	/// @param ppRC return the address of a graphics device handle created.
	/// @param ppDC return the address of a window context handle created.
	/// @return type HRESULT  
	HRESULT create_context_from_hwnd(
		HWND hwnd,
		HGLRC* ppRC,
		HDC* ppDC,
		bool enable_directx_integration = false);

	/// @brief 
	/// @param name : return bool supported extension by name
	/// @return 
	bool	has_extension(const char* name);

	/// @brief release the resource of HGLRC and HDC
	/// @param hwnd specifies the window andle
	/// @param rc the graphic device of the object to free resource of
	/// @param dc the device context of the object to free resource of
	void release_context(HWND hwnd, HGLRC* rc, HDC* dc);
};
