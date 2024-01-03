#include "WindowManager.h"

#include <cstdlib>
#include <iostream>

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void WindowManager::RegisterWindowClass(HINSTANCE hInstance) {

    this->window_class.lpfnWndProc   = MainWindowProc;
    this->window_class.hInstance     = hInstance;
    this->window_class.lpszClassName = MAIN_WINDOW_CLASS_NAME;

    RegisterClass(&this->window_class);
}

void WindowManager::Init(HINSTANCE hInstance) {

#ifdef USE_DEBUG_CONSOLE
    this->StartDebugConsole();
#endif

    this->RegisterWindowClass(hInstance);

    this->hwnd = CreateWindowEx(
        MAIN_WINDOW_OPTIONAL_STYLES,
        MAIN_WINDOW_CLASS_NAME,
        MAIN_WINDOW_TITLE,
        MAIN_WINDOW_STYLE,

        MAIN_WINDOW_POS_X, MAIN_WINDOW_POS_Y, MAIN_WINDOW_SIZE_W, MAIN_WINDOW_SIZE_H,

        NULL,      // Parent window
        NULL,      // Menu
        hInstance, // Instance handle
        NULL       // Additional application data
    );

    if (this->hwnd == NULL) {
        exit(1);
    }

    ShowWindow(this->hwnd, 1);
}

void WindowManager::Deinit() {

#ifdef USE_DEBUG_CONSOLE
    FreeConsole();
#endif
}

void WindowManager::MessageLoop() {

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void WindowManager::Start() {

    static bool is_started = false;

    if (!is_started) {
        this->message_thread = new std::thread(&WindowManager::MessageLoop);
        this->message_thread->detach();
    }

}

void WindowManager::Loop() {
    MessageLoop();
}

void WindowManager::StartDebugConsole() {

    FILE* file = nullptr;
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    freopen_s(&file, "CONOUT$", "w", stdout);
    SetConsoleTitle(DEBUG_CONSOLE_TITLE);
    std::cout << "Debug console started" << std::endl;
}

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}