#include <Windows.h>
#include "Win32/WindowFactory.h"
#include <iostream>
#include <memory>

using namespace std;


int APIENTRY wWinMain(
    _In_        HINSTANCE hInstance,
    _In_opt_    HINSTANCE hPrevInstance,
    _In_        LPWSTR    lpCmdLine,
    _In_        int       nCmdShow)
{

    WindowFactory::SethInstance(hInstance);
    auto mainWindow = WindowFactory::Build(250, 80, 640, 480);
    if (mainWindow) {
        mainWindow->Process();
    }

    return 0;
}