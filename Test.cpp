#include <Windows.h>
#include <iostream>
#include <memory>
#include "Win32/WindowFactory.h"
#include "Render/RenderFactory.h"

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
        RenderFactory::InitRender(RenderFactory::RenderType_Direct2D);
        auto render = RenderFactory::GetInstance();

        mainWindow->Process();
    }

    return 0;
}