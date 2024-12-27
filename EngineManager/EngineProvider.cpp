#include "EngineProvider.h"

EngineProvider* EngineProvider::g_eng = nullptr;

// 构造
EngineProvider::EngineProvider() {

}

// 析构
EngineProvider::~EngineProvider() {

}

// 初始化
void EngineProvider::InitEngine() {
	if (!g_eng) {
		g_eng = new EngineProvider();
	}
}

// 初始化引擎
void EngineProvider::InitEngine(HINSTANCE _hinst) {
	if (g_eng) {
		g_eng->engine_hInstance = _hinst;
	}
}