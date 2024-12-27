#include <Windows.h>
#include <iostream>
#include <memory>
#include <thread>
#include "Win32/WindowFactory.h"
#include "Render/RenderFactory.h"
#include "Umg/UIFactory.h"
#include "Timer/TimerFactory.h"
#include "Render/Sprite/Animation.h"

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
    }

    subhandle->join();

    return 0;
}

void subthread() {

    // 初始化模块
    UIFactory::InitUIProvider();
    TimerFactory::InitTimerFactory();

    Animation* _test = new Animation();
    if (_test) {
        std::string path = "C:\\Users\\asus\\Pictures\\39\\Units\\1-1.png";
        for (auto i = 0; i < 8;i++) {
            SImage* newone = new SImage(path.c_str());
            if (newone) {
                newone->SetLocaiton(50, 50);
                newone->SetSize(36, 36);
                newone->SetCrop(i * 36, 0, 36, 36);
            }
            _test->AddSprite(newone);
        }
        _test->SetPlaySpeed(8);
    }

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

                if (_test) {
                    _test->Draw();
                }

                render->EndPlay();
            }
        }
    }


    UIFactory::Release();
    TimerFactory::Release();
}