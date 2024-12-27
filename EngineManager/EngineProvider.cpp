#include "EngineProvider.h"

EngineProvider* EngineProvider::g_eng = nullptr;

// ����
EngineProvider::EngineProvider() {

}

// ����
EngineProvider::~EngineProvider() {

}

// ��ʼ��
void EngineProvider::InitEngine() {
	if (!g_eng) {
		g_eng = new EngineProvider();
	}
}

// ��ʼ������
void EngineProvider::InitEngine(HINSTANCE _hinst) {
	if (g_eng) {
		g_eng->engine_hInstance = _hinst;
	}
}