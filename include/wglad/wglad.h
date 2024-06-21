#pragma once

#define WIN32_LEAN_AND_MEAN 1
#pragma comment(lib, "opengl32")

#pragma warning(disable:4005)

#include "wglad/glad.h"
#include <windows.h>
#include "wglad/wglext.h"

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>


#define GL_EXT_PROC(type, func) \
do{\
	char buf[128]; \
	if(func) { \
		sprintf_s(buf, "file : %s\nline : %d\n%s's already exist.", __FILE__, __LINE__, #func); \
		if(MessageBoxA(NULL, buf, "Error", MB_OK)) exit(0); \
	}\
    func = (type)wglGetProcAddress(#func);\
	if(!func) { \
		sprintf_s(buf, "file : %s\nline : %d\n%s's failed to load.", __FILE__, __LINE__, #func); \
		if(MessageBoxA(NULL, buf, "Error", MB_OK)) exit(0); \
	}\
}while(false)

GLAPI PFNWGLCHOOSEPIXELFORMATARBPROC			_wglChoosePixelFormatARB;
GLAPI PFNWGLCREATECONTEXTATTRIBSARBPROC         _wglCreateContextAttribsARB;
GLAPI PFNWGLMAKECONTEXTCURRENTARBPROC			_wglMakeContextCurrentARB;
GLAPI PFNWGLSWAPINTERVALEXTPROC					_wglSwapIntervalEXT;
#define wglChoosePixelFormatARB					_wglChoosePixelFormatARB
#define wglCreateContextAttribsARB				_wglCreateContextAttribsARB
#define wglMakeContextCurrentARB 				_wglMakeContextCurrentARB
#define wglSwapIntervalEXT						_wglSwapIntervalEXT

namespace wglad {

	/// @brief load glad function pointers and extensions
	void 	load_gl_extension();

	/// @brief create the resouce of Graphics Device
	/// @param hwnd specifies the window handle
	/// @param ppRC return the address of a graphics device handle created.
	/// @param ppDC return the address of a window context handle created.
	/// @return type HRESULT  
	HRESULT create_context_from_hwnd(_In_ HWND hwnd, _Out_ HGLRC* ppRC, _Out_ HDC* ppDC);

	/// @brief 
	/// @param name : return bool supported extension by name
	/// @return 
	bool	has_extension(const char* name);

	/// @brief release the resource of HGLRC and HDC
	/// @param hwnd specifies the window andle
	/// @param rc the graphic device of the object to free resource of
	/// @param dc the device context of the object to free resource of
	void release_context(HWND hwnd, HGLRC rc, HDC dc);
};
