#include "EngineProvider.h"

int EngineProvider::buildEngine_state = 0;
EngineProvider* EngineProvider::g_eng = nullptr;

// 构造
EngineProvider::EngineProvider() {
	// 属性
	engine_hInstance = nullptr; // 进程句柄
	update_Thread = nullptr;	// 更新用线程
	render_Thread = nullptr;	// 渲染用线程
	updateState = 0;			// 更新 - 状态
	renderState = 0;			// 渲染 - 状态

}

// 析构
EngineProvider::~EngineProvider() {

}

// 获取引擎
EngineProvider* EngineProvider::GetInstance() {
	return g_eng;
}

// 初始化
void EngineProvider::InitEngine() {
	if (!g_eng) {
		g_eng = new EngineProvider();
	}
	g_eng->BuildEngineStruct();
}

// 初始化引擎
void EngineProvider::InitEngine(HINSTANCE _hinst) {
	if (!g_eng) {
		g_eng = new EngineProvider();
	}
	g_eng->engine_hInstance = _hinst;
	g_eng->BuildEngineStruct();
}

// 运行引擎
void EngineProvider::RunEngine() {
	if (g_eng) {
		g_eng->MainRunLoop();
	}
}

// 构建引擎
void EngineProvider::BuildEngineStruct() {
	if (buildEngine_state == 1) {
		return;
	}

	// 读取引擎配置文件


	// 开始构建
	// 构建计时器系统
	TimerFactory::InitTimerFactory();

	// 构建Win32系统
	WindowFactory::SethInstance(engine_hInstance);
	this->mainWindow = WindowFactory::Build(250, 80, 640, 480);

	// 构建渲染系统
	RenderFactory::InitRender(RenderFactory::RenderType_Direct2D, mainWindow->GetHandle(), 640, 480);

	// 构建UI系统
	UIFactory::InitUIProvider();

	// 构建独立线程
	updateState = 1;
	renderState = 1;
	update_Thread = new std::thread(&EngineProvider::ThreadLoop_RunUpdate, this);
	render_Thread = new std::thread(&EngineProvider::ThreadLoop_RunRender, this);

	buildEngine_state = 1;
}

// 主线程运行
void EngineProvider::MainRunLoop() {
	// win32窗口消息
	if (mainWindow) {
		mainWindow->Process();
	}

	// 等待线程结束
	WaittingThreadProcess();

	// 其他模块处理
	UIFactory::Release();			// UI模块
	RenderFactory::Release();		// 渲染器模块
	TimerFactory::Release();		// 计时器模块

}

// 更新用线程
void EngineProvider::ThreadLoop_RunUpdate() {

	while (updateState) {
		// UI系统 更新
		UIFactory::Update();
	}
	{
		std::unique_lock<std::mutex> lock(lock_update);
		updateState = 2;
		cv_update.notify_one();
	}

}

// 渲染用线程
void EngineProvider::ThreadLoop_RunRender() {
	while (renderState) {
		// 渲染
		auto renderFactory = RenderFactory::GetInstance();
		if (renderFactory) {
			auto render = renderFactory->GetRender();
			if (render) {
				// 开始渲染
				render->BeginPlay();

				// UI系统 渲染
				UIFactory::Draw();



				// 结束渲染
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

// 等待线程结束
void EngineProvider::WaittingThreadProcess() {
	// 等待线程结束

	// 更新线程
	{
		updateState = 0;
		std::unique_lock<std::mutex> lock(lock_update);
		cv_update.wait(lock, [&]() {
			return updateState == 2;
		});
	}

	// 渲染线程
	{
		renderState = 0;
		std::unique_lock<std::mutex> lock(lock_render);
		cv_render.wait(lock, [&]() {
			return renderState == 2;
		});
	}
}