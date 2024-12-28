#include "SceneManager.h"


SceneManager* SceneManager::g_sceneManger = nullptr;

// 构造
SceneManager::SceneManager() {

}

// 析构
SceneManager::~SceneManager() {

}


// 初始化引擎
void SceneManager::InitSceneManager() {
	// 实例化
	auto handle = GetInstance();


}

// 释放
void SceneManager::Release() {

}

// 获取引擎
SceneManager* SceneManager::GetInstance() {
	if (!g_sceneManger) {
		g_sceneManger = new SceneManager();
	}
	return g_sceneManger;
}

// 更新
void SceneManager::UpdateScene() {
	if (g_sceneManger) {
		
	}
}

// 绘制
void SceneManager::DrawScene() {
	if (g_sceneManger) {

	}
}
