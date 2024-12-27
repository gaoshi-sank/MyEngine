#ifndef _EngineProvider_h_
#define _EngineProvider_h_

#include "EngineConfig.h"
#include "Win32/WindowFactory.h"
#include "Render/RenderFactory.h"
#include "Umg/UIFactory.h"
#include "Timer/TimerFactory.h"
#include "Render/Sprite/Animation.h"

// ���������
class EngineProvider {
private:
	// ����
	EngineProvider();

	// ����
	~EngineProvider();

	// ��ֵ̬
	static EngineProvider* g_eng;

	// ����
	HINSTANCE engine_hInstance;

public:
	// ��ʼ������
	static void InitEngine();

	// ��ʼ������
	static void InitEngine(HINSTANCE _hinst);

private:

};

#endif // !_EngineProvider_h_
