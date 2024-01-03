#ifndef UNICODE
#define UNICODE
#endif 

#include "WindowManager.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    WindowManager* wm = &WindowManager::getInstance();

    wm->Init(hInstance);
    wm->Loop();

    return 0;
}
