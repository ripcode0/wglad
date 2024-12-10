#include <iostream>
#include <windows.h>
#include <wglad/wglad.h>

LRESULT WINAPI proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(EXIT_SUCCESS);
        break;
    case WM_KEYDOWN:
        if(wp == VK_ESCAPE){
            DestroyWindow(hwnd);
        }
        break;
    default:
        break;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

int main(int args, char* argv[])
{
    WNDCLASSEX wc{};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = proc;
    wc.lpszClassName = TEXT("Win32++");
    
    if(!RegisterClassEx(&wc)){
        printf("failed to register class %s\n", wc.lpszClassName);
        exit(EXIT_FAILURE);
    }

    HWND hwnd = CreateWindowEx(
        0, wc.lpszClassName, wc.lpszClassName,
        WS_OVERLAPPEDWINDOW, 
        200, 200, 1024, 780, 0, 0, wc.hInstance, 0
    );

    HDC dc{};
    HGLRC rc{};

    wglad::create_context_from_hwnd(hwnd, &rc, &dc);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg{};
    while (msg.message != WM_QUIT)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if(rc && dc){
                glClearColor(0.2f, 0.25f, 0.3f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                //rendering

                ::SwapBuffers(dc);
            }
        }
        
    }

    wglad::release_context(hwnd, &rc, &dc);
       
    return 0;
}