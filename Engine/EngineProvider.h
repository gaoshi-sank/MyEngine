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
	static int buildEngine_state;
	static EngineProvider* g_eng;

	// ����
	HINSTANCE engine_hInstance;			// ���̾��
	std::shared_ptr<Window> mainWindow;	// ������
	std::thread* update_Thread;			// �������߳�
	std::thread* render_Thread;			// ��Ⱦ���߳�
	int updateState;					// ���� - ״̬
	int renderState;					// ��Ⱦ - ״̬
	std::mutex lock_update;				// �� - ����
	std::mutex lock_render;				// �� - ��Ⱦ
	std::condition_variable cv_update;	// ���� - ����
	std::condition_variable cv_render;	// ���� - ��Ⱦ


public:
	// ��ȡ����
	static EngineProvider* GetInstance();

	// ��ʼ������
	static void InitEngine();

	// ��ʼ������
	static void InitEngine(HINSTANCE _hinst);

	// ��������
	static void RunEngine();

private:
	// ��������
	void BuildEngineStruct();

	// ���߳�����
	void MainRunLoop();

	// �������߳�
	void ThreadLoop_RunUpdate();

	// ��Ⱦ���߳�
	void ThreadLoop_RunRender();

	// �ȴ��߳̽���
	void WaittingThreadProcess();

};

#endif // !_EngineProvider_h_
