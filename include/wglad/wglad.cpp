#include "wglad/wglad.h"

static void fatal_error(char *msg)
{
    MessageBoxA(NULL, msg, "Error", MB_OK | MB_ICONEXCLAMATION);
    exit(EXIT_FAILURE);
}

PFNWGLCHOOSEPIXELFORMATARBPROC			_wglChoosePixelFormatARB = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC       _wglCreateContextAttribsARB = NULL;
PFNWGLMAKECONTEXTCURRENTARBPROC			_wglMakeContextCurrentARB = NULL;
PFNWGLSWAPINTERVALEXTPROC				_wglSwapIntervalEXT = NULL;

void WGL::LoadGLExtension()
{
    static bool isLoaded = false;
    if(isLoaded) return;

	HWND hwnd = CreateWindowEx(NULL, TEXT("STATIC"), TEXT(""), NULL, 0, 0,
		0, 0, NULL, NULL, GetModuleHandle(NULL), NULL);

	HDC dc = GetDC(hwnd);

	PIXELFORMATDESCRIPTOR pfd{};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cAlphaBits = 8;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixelFormat = ::ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);
	HGLRC rc = wglCreateContext(dc);
    
	wglMakeCurrent(dc, rc);

	//gladLoadGLLoader();
	//gladLoadGL();
	GL_EXT_PROC(PFNWGLCHOOSEPIXELFORMATARBPROC, wglChoosePixelFormatARB);
	GL_EXT_PROC(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB);
	GL_EXT_PROC(PFNWGLMAKECONTEXTCURRENTARBPROC, wglMakeContextCurrentARB);
	GL_EXT_PROC(PFNWGLSWAPINTERVALEXTPROC, wglSwapIntervalEXT);

	if(!gladLoadGL()){
		fatal_error("failed to load glad");
	}
    
	wglMakeCurrent(0, 0);
	wglDeleteContext(rc);
	ReleaseDC(hwnd, dc);
	DestroyWindow(hwnd);

    isLoaded = true;
}
HRESULT WGL::LoadGladFromHwnd(_In_ HWND hwnd,_Out_ HGLRC* ppRC, _Out_ HDC* ppDC)
{
	LoadGLExtension();
	//if(!rc && !dc) return E_INVALIDARG;
	HDC dc = GetDC(hwnd);
	HGLRC rc = nullptr;

	if (WGL_ARB_create_context && WGL_ARB_pixel_format)
	{
		int pixelFormatAttribs[] =
		{
			WGL_SUPPORT_OPENGL_ARB,		GL_TRUE,
			WGL_COLOR_BITS_ARB,			32,
			WGL_DEPTH_BITS_ARB,			24,
			WGL_STENCIL_BITS_ARB,		8,
			WGL_DOUBLE_BUFFER_ARB,		GL_TRUE,
			0
		};

		float pixelFormatFloatAttribs[] = { 0.0f };

		int contextAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 6,
			WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			WGL_CONTEXT_RELEASE_BEHAVIOR_ARB, WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB,
			0
		};

		int pixelFormat;
		int numFormats;
		if (!wglChoosePixelFormatARB(dc, pixelFormatAttribs,
			pixelFormatFloatAttribs, 1, &pixelFormat, (unsigned int*)&numFormats))
		{
			fatal_error("failed to find pixel format from attribs");
		}

		PIXELFORMATDESCRIPTOR pfd{};		//get more infomation of pixel format
		DescribePixelFormat(dc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

		if (!SetPixelFormat(dc, pixelFormat, &pfd))
			fatal_error("failed to set pixel format");

		rc = wglCreateContextAttribsARB(dc, 0, contextAttribs);

		if(!rc) return E_NOTIMPL;
		
		wglMakeCurrent(dc, rc);
	}
	else{
		return E_NOINTERFACE;
	}
	
	const char* version = (char*)glGetString(GL_VERSION);
	const char* vendor = (char*)glGetString(GL_VENDOR);
	const char* hardware = (char*)glGetString(GL_RENDERER);
	const char* glslVer = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	
	// char apiInfo[128]{};
	// sprintf_s(apiInfo, "API  : OpenGL %s\nGLSL : %s\nHW   : %s\n", version, glslVer, hardware);
	// printf(apiInfo);
	//std::move(pDC)
	*ppDC = dc;
	*ppRC = rc;

    return S_OK;
}

