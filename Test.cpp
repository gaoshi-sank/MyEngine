#include <Windows.h>
#include <iostream>
#include <memory>
#include <thread>
#include "Win32/WindowFactory.h"
#include "Render/RenderFactory.h"
#include "Umg/UIFactory.h"
#include "Timer/TimerFactory.h"

using namespace std;
int status = 1;

// 函数声明
void subthread();

// 主函数
int APIENTRY wWinMain(
    _In_        HINSTANCE hInstance,
    _In_opt_    HINSTANCE hPrevInstance,
    _In_        LPWSTR    lpCmdLine,
    _In_        int       nCmdShow)
{
    std::thread* subhandle = nullptr;
    WindowFactory::SethInstance(hInstance);
    auto mainWindow = WindowFactory::Build(250, 80, 640, 480);
    if (mainWindow) {
        // 处理渲染器
        RenderFactory::InitRender(RenderFactory::RenderType_Direct2D, mainWindow->GetHandle(), 640, 480);
        subhandle = new thread(subthread);

        // Win32消息循环
        mainWindow->Process();

        // 结束处理
        status = 0;
        UIFactory::Release();
        TimerFactory::Release();
    }

    subhandle->join();

    return 0;
}

void subthread() {

    // 初始化模块
    UIFactory::InitUIProvider();
    TimerFactory::InitTimerFactory();

    std::string testpath = "C:\\Users\\asus\\Pictures\\39\\Common\\9-1.png";
    UI_Button* _test = new UI_Button();
    if(_test){
        _test->Create(testpath, 100, 50, 100, 50);
        _test->AddStaticText("Hello World!");
    }

    UI_Button* _test2 = new UI_Button();
    if (_test2) {
        _test2->Create(testpath, 150, 50, 100, 50);
        _test2->AddStaticText("Hello World!");
    }

    TimerFactory::SetTimer([](int* param) {
        status = 0;
    }, 5000.0f, false);

    while (status) {
        // 更新
        UIFactory::Update();

        // 渲染
        auto renderFactory = RenderFactory::GetInstance();
        if (renderFactory) {
            auto render = renderFactory->GetRender();
            if (render) {
                render->BeginPlay();
                
                // 渲染UI
                UIFactory::Draw();


                render->EndPlay();
            }
        }
    }

}