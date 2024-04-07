#include "wglad/wglad.h"

static void wglad_error(char *msg)
{
    MessageBoxA(NULL, msg, "Error", MB_OK | MB_ICONEXCLAMATION);
    exit(EXIT_FAILURE);
}

PFNWGLCHOOSEPIXELFORMATARBPROC			_wglChoosePixelFormatARB = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC       _wglCreateContextAttribsARB = NULL;
PFNWGLMAKECONTEXTCURRENTARBPROC			_wglMakeContextCurrentARB = NULL;
PFNWGLSWAPINTERVALEXTPROC				_wglSwapIntervalEXT = NULL;

void WGL::loadGLExtension()
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

	GL_EXT_PROC(PFNWGLCHOOSEPIXELFORMATARBPROC, wglChoosePixelFormatARB);
	GL_EXT_PROC(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB);
	GL_EXT_PROC(PFNWGLMAKECONTEXTCURRENTARBPROC, wglMakeContextCurrentARB);
	GL_EXT_PROC(PFNWGLSWAPINTERVALEXTPROC, wglSwapIntervalEXT);

	if(!gladLoadGL()){
		wglad_error("failed to load glad");
	}
    
	wglMakeCurrent(0, 0);
	wglDeleteContext(rc);
	ReleaseDC(hwnd, dc);
	DestroyWindow(hwnd);

    isLoaded = true;
}

void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

HRESULT WGL::createGLContextFromHwnd(_In_ HWND hwnd,_Out_ HGLRC* ppRC, _Out_ HDC* ppDC)
{
	loadGLExtension();
	
	HDC dc = GetDC(hwnd);
	HGLRC rc = nullptr;

	if (WGL_ARB_create_context && WGL_ARB_pixel_format)
	{
		int pixelFormatAttribs[] = {
			WGL_SUPPORT_OPENGL_ARB, 	GL_TRUE,
			WGL_DRAW_TO_WINDOW_ARB, 	GL_TRUE,
			WGL_ACCELERATION_ARB, 		WGL_FULL_ACCELERATION_ARB,
			WGL_COLOR_BITS_ARB, 		32,
			WGL_DEPTH_BITS_ARB, 		24,
			WGL_STENCIL_BITS_ARB,		8,
			WGL_SWAP_METHOD_ARB, 		WGL_SWAP_EXCHANGE_ARB,
			//WGL_SWAP_METHOD_ARB, 		WGL_SWAP_COPY_ARB,
			WGL_PIXEL_TYPE_ARB, 		WGL_TYPE_RGBA_ARB,
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
			wglad_error("failed to find pixel format from attribs");
		}

		PIXELFORMATDESCRIPTOR pfd{};		//get more infomation of pixel format
		DescribePixelFormat(dc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

		if (!SetPixelFormat(dc, pixelFormat, &pfd))
			wglad_error("failed to set pixel format");

		rc = wglCreateContextAttribsARB(dc, 0, contextAttribs);

		if(!rc) return E_NOTIMPL;
		
		wglMakeCurrent(dc, rc);
	}
	else{
		return E_NOINTERFACE;
	}

	if (GL_ARB_clip_control) {
		//https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_clip_control.txt
		glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
		glDepthRange(0.0f, 1.0f);
	}
	if (GL_ARB_direct_state_access) {
		printf("DSA is supported\n");
	}

	if(hasExtension("GL_ARB_direct_state_access")){
		printf("DSA enabled");
	}

	if (GL_KHR_debug) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_ERROR,
			GL_DONT_CARE, 0, nullptr, GL_TRUE);
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

bool WGL::hasExtension(const char *name)
{
	GLint nExtensions{};
	glGetIntegerv(GL_NUM_EXTENSIONS , &nExtensions);

	for(int i = 0; i < nExtensions; ++i){
		const char* ext = (const char*)glGetStringi(GL_EXTENSIONS, i);
		if(strcmp(ext, name) == 0){
			return true;
		}
	}
    return false;
}
void WGL::releaseGLContext(HWND hwnd, HGLRC rc, HDC dc)
{
	wglMakeCurrent(0, 0);
	wglDeleteContext(rc);
	ReleaseDC(hwnd, dc);
	rc = nullptr;
	dc = nullptr;
}

void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id,
                              GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	//ingnore warnings
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "OpenGL debug message" << std::endl;
	std::cout << "Source: ";

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		std::cout << "API";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		std::cout << "APPLICATION";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		std::cout << "OTHER";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		std::cout << "SHADER COMPILER";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		std::cout << "THIRD PARTY";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		std::cout << "WINDOW SYSTEM";
		break;
	}

	std::cout << std::endl;
	std::cout << "Type: ";

	switch (type)
	{
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "DEPRECATED BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_MARKER:
		std::cout << "MARKER";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "OTHER";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		std::cout << "POP GROUP";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		std::cout << "PUSH GROUP";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "UNDEFINED BEHAVIOR";
		break;
	}

	std::cout << std::endl;
	std::cout << "ID: " << id << std::endl;
	std::cout << "Severity: ";

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "HIGH";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::cout << "NOTIFICATION";
		break;
	}

	std::cout << std::endl;
	std::cout << "Message: " << message << std::endl;

	std::string debugMsg("Debug Index : ");
	/*debugMsg += std::to_string(debugIndex) + "\n";*/
	debugMsg += message;

	const int result = MessageBoxA(NULL, debugMsg.c_str(), "GL_KHR_debug", MB_OKCANCEL);

	switch (result)
	{
	case IDOK:
		break;
	case IDCANCEL:
		exit(0);
		break;
	default:
		break;
	}
}