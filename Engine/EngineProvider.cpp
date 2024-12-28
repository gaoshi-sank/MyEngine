#include "EngineProvider.h"

int EngineProvider::buildEngine_state = 0;
EngineProvider* EngineProvider::g_eng = nullptr;

// ����
EngineProvider::EngineProvider() {
	// ����
	engine_hInstance = nullptr; // ���̾��
	update_Thread = nullptr;	// �������߳�
	render_Thread = nullptr;	// ��Ⱦ���߳�
	updateState = 0;			// ���� - ״̬
	renderState = 0;			// ��Ⱦ - ״̬

}

// ����
EngineProvider::~EngineProvider() {

}

// ��ȡ����
EngineProvider* EngineProvider::GetInstance() {
	return g_eng;
}

// ��ʼ��
void EngineProvider::InitEngine() {
	if (!g_eng) {
		g_eng = new EngineProvider();
	}
	g_eng->BuildEngineStruct();
}

// ��ʼ������
void EngineProvider::InitEngine(HINSTANCE _hinst) {
	if (!g_eng) {
		g_eng = new EngineProvider();
	}
	g_eng->engine_hInstance = _hinst;
	g_eng->BuildEngineStruct();
}

// ��������
void EngineProvider::RunEngine() {
	if (g_eng) {
		g_eng->MainRunLoop();
	}
}

// ��������
void EngineProvider::BuildEngineStruct() {
	if (buildEngine_state == 1) {
		return;
	}

	// ��ȡ���������ļ�


	// ��ʼ����
	// ������ʱ��ϵͳ
	TimerFactory::InitTimerFactory();

	// ����Win32ϵͳ
	WindowFactory::SethInstance(engine_hInstance);
	this->mainWindow = WindowFactory::Build(250, 80, 640, 480);

	// ������Ⱦϵͳ
	RenderFactory::InitRender(RenderFactory::RenderType_Direct2D, mainWindow->GetHandle(), 640, 480);

	// ����UIϵͳ
	UIFactory::InitUIProvider();

	// ���������߳�
	updateState = 1;
	renderState = 1;
	update_Thread = new std::thread(&EngineProvider::ThreadLoop_RunUpdate, this);
	render_Thread = new std::thread(&EngineProvider::ThreadLoop_RunRender, this);

	buildEngine_state = 1;
}

// ���߳�����
void EngineProvider::MainRunLoop() {
	// win32������Ϣ
	if (mainWindow) {
		mainWindow->Process();
	}

	// �ȴ��߳̽���
	WaittingThreadProcess();

	// ����ģ�鴦��
	UIFactory::Release();			// UIģ��
	RenderFactory::Release();		// ��Ⱦ��ģ��
	TimerFactory::Release();		// ��ʱ��ģ��

}

// �������߳�
void EngineProvider::ThreadLoop_RunUpdate() {

	while (updateState) {
		// UIϵͳ ����
		UIFactory::Update();
	}
	{
		std::unique_lock<std::mutex> lock(lock_update);
		updateState = 2;
		cv_update.notify_one();
	}

}

// ��Ⱦ���߳�
void EngineProvider::ThreadLoop_RunRender() {
	while (renderState) {
		// ��Ⱦ
		auto renderFactory = RenderFactory::GetInstance();
		if (renderFactory) {
			auto render = renderFactory->GetRender();
			if (render) {
				// ��ʼ��Ⱦ
				render->BeginPlay();

				// UIϵͳ ��Ⱦ
				UIFactory::Draw();



				// ������Ⱦ
				render->EndPlay();
			}
		}
	}
	{
		std::unique_lock<std::mutex> lock(lock_render);
		renderState = 2;
		cv_render.notify_one();
	}
}

// �ȴ��߳̽���
void EngineProvider::WaittingThreadProcess() {
	// �ȴ��߳̽���

	// �����߳�
	{
		updateState = 0;
		std::unique_lock<std::mutex> lock(lock_update);
		cv_update.wait(lock, [&]() {
			return updateState == 2;
		});
	}

	// ��Ⱦ�߳�
	{
		renderState = 0;
		std::unique_lock<std::mutex> lock(lock_render);
		cv_render.wait(lock, [&]() {
			return renderState == 2;
		});
	}
}