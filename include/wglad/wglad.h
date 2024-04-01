#pragma once

#define WIN32_LEAN_AND_MEAN 1
#pragma comment(lib, "opengl32")

#pragma warning(disable:4005)



#include "wglad/glad.h"
#include <windows.h>
#include "wglad/wglext.h"

//#include <GL/GL.h> //[GL_VERSION_1_1]
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>


// typedef BOOL (WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
// typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
// typedef BOOL (WINAPI * PFNWGLMAKECONTEXTCURRENTARBPROC) (HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
// typedef BOOL (WINAPI * PFNWGLSWAPINTERVALEXTPROC) (int interval);

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

namespace WGL {
    void LoadGLExtension();
    HRESULT LoadGladFromHwnd(_In_ HWND hwnd,_Out_ HGLRC* ppRC, _Out_ HDC* ppDC);
};