#include <Windows.h>
#include "EngineManager/EngineProvider.h"


// 函数声明
void subthread();

// 主函数
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