#include <Windows.h>
#include "Engine/EngineProvider.h"


// Ö÷º¯Êý
int APIENTRY wWinMain(
    _In_        HINSTANCE hInstance,
    _In_opt_    HINSTANCE hPrevInstance,
    _In_        LPWSTR    lpCmdLine,
    _In_        int       nCmdShow)
{
    EngineProvider::InitEngine(hInstance);
    EngineProvider::RunEngine();
    return 0;
}