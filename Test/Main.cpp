#include "../Engine/EngineProvider.h"
#include "Scene_Test.h"

// Ö÷º¯Êý
int APIENTRY wWinMain(
    _In_        HINSTANCE hInstance,
    _In_opt_    HINSTANCE hPrevInstance,
    _In_        LPWSTR    lpCmdLine,
    _In_        int       nCmdShow)
{
    LogI("game begin");
    EngineProvider::InitEngine(hInstance, RenderFactory::RenderType_Direct2D);

    SceneManager::AddScene(new Scene_Test());

    EngineProvider::RunEngine();

    LogI("game end");
    return 0;
}