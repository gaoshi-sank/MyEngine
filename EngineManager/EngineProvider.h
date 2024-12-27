#ifndef _EngineProvider_h_
#define _EngineProvider_h_

#include "EngineConfig.h"
#include "Win32/WindowFactory.h"
#include "Render/RenderFactory.h"
#include "Umg/UIFactory.h"
#include "Timer/TimerFactory.h"
#include "Render/Sprite/Animation.h"

// 引擎管理类
class EngineProvider {
private:
	// 构造
	EngineProvider();

	// 析构
	~EngineProvider();

	// 静态值
	static EngineProvider* g_eng;

	// 属性
	HINSTANCE engine_hInstance;

public:
	// 初始化引擎
	static void InitEngine();

	// 初始化引擎
	static void InitEngine(HINSTANCE _hinst);

private:

};

#endif // !_EngineProvider_h_
