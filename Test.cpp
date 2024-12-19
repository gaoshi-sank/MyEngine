#include <Windows.h>
#include <iostream>
#include <memory>
#include <thread>
#include "Win32/WindowFactory.h"
#include "Render/RenderFactory.h"
#include "Render/Sprite/SSprite.h"

using namespace std;
int status = 1;

void subthread();


int APIENTRY wWinMain(
    _In_        HINSTANCE hInstance,
    _In_opt_    HINSTANCE hPrevInstance,
    _In_        LPWSTR    lpCmdLine,
    _In_        int       nCmdShow)
{
    WindowFactory::SethInstance(hInstance);
    auto mainWindow = WindowFactory::Build(250, 80, 640, 480);
    if (mainWindow) {
        // 处理渲染器
        RenderFactory::InitRender(RenderFactory::RenderType_Direct2D, mainWindow->GetHandle(), 640, 480);
        auto sub = new thread(subthread);
        sub->detach();

        // Win32消息循环
        mainWindow->Process();

        // 结束处理
        status = 0;
    }

    while (status != 2);

    return 0;
}

void subthread() {

    SImage* _test = new SImage("C:\\Users\\asus\\Pictures\\39\\Title\\1-1.bmp");
    SText* _test2 = new SText("世界，你好！");
    _test2->SetLocaiton(100, 50);
    _test2->SetSize(100, 50);
    _test2->ReSetColor(255, 255, 255);

    while (status) {
        auto renderFactory = RenderFactory::GetInstance();
        if (renderFactory) {
            auto render = renderFactory->GetRender();
            if (render) {
                render->BeginPlay();

                if (_test) {
                //    _test->Draw();
                }

                if (_test2) {
                    _test2->Draw();
                }

                render->EndPlay();
            }
        }
    }
    status = 2;

}