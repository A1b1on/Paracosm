#pragma once

#include "WindowManagerConfig.h"

#include <Windows.h>
#include <thread>

class WindowManager
{
    WindowManager() {}
    WindowManager(const WindowManager&) {}
    void operator=(const WindowManager&){}

    WNDCLASS window_class;
    void RegisterWindowClass(HINSTANCE hInstance);

    HWND         hwnd;
    std::thread* message_thread;
    static void  MessageLoop();

    void StartDebugConsole();
public:

    static WindowManager& getInstance() {

        static WindowManager wm_instance;
        return wm_instance;
    }

    void Init(HINSTANCE hInstances);
    void Deinit();

    void Start();
    void Loop();
};

