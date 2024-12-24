#include <Windows.h>
#include <iostream>
#include <memory>
#include <thread>
#include "Win32/WindowFactory.h"
#include "Render/RenderFactory.h"
#include "Umg/UIFactory.h"

using namespace std;
int status = 1;

// ��������
void subthread();

// ������
int APIENTRY wWinMain(
    _In_        HINSTANCE hInstance,
    _In_opt_    HINSTANCE hPrevInstance,
    _In_        LPWSTR    lpCmdLine,
    _In_        int       nCmdShow)
{
    WindowFactory::SethInstance(hInstance);
    auto mainWindow = WindowFactory::Build(250, 80, 640, 480);
    if (mainWindow) {
        // ������Ⱦ��
        RenderFactory::InitRender(RenderFactory::RenderType_Direct2D, mainWindow->GetHandle(), 640, 480);
        auto sub = new thread(subthread);
        sub->detach();

        // Win32��Ϣѭ��
        mainWindow->Process();

        // ��������
        status = 0;
    }

    while (status != 2);

    return 0;
}

void subthread() {


    // ��ʼ��UI�׼�
    UIFactory::InitUIProvider();

    std::string testpath = "C:\\Users\\asus\\Pictures\\39\\Common\\9-1.png";
    UI_CheckBox* _test = new UI_CheckBox();
    if(_test){
        _test->Create(testpath, 0, 0, 100, 50);
        _test->AddStaticText("Hello World!");
    }

    UI_CheckBox* _test2 = new UI_CheckBox();
    if (_test2) {
        _test2->Create(testpath, 150, 80, 100, 50);
        _test2->AddStaticText("Hello World!");
    }


    while (status) {
        // ����
        UIFactory::Update();

        // ��Ⱦ
        auto renderFactory = RenderFactory::GetInstance();
        if (renderFactory) {
            auto render = renderFactory->GetRender();
            if (render) {
                render->BeginPlay();
                
                // ��ȾUI
                UIFactory::Draw();


                render->EndPlay();
            }
        }
    }
    status = 2;

}