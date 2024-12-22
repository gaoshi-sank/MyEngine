#include <Windows.h>
#include <iostream>
#include <memory>
#include <thread>
#include "Win32/WindowFactory.h"
#include "Render/RenderFactory.h"
#include "Umg/UIFactory.h"

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

    std::string testpath = "C:\\Users\\asus\\Pictures\\39\\Common\\116-1.png";
    UI_Lable* _test = new UI_Lable();
    if(_test){
        _test->Create(testpath, 0, 0, 100, 50);
        _test->AddStaticText("Hello World!");
    }


    while (status) {
        auto renderFactory = RenderFactory::GetInstance();
        if (renderFactory) {
            auto render = renderFactory->GetRender();
            if (render) {
                render->BeginPlay();

                if (_test) {
                    _test->Draw();
                }


                render->EndPlay();
            }
        }
    }
    status = 2;

}