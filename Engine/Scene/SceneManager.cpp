#include "SceneManager.h"


SceneManager* SceneManager::g_sceneManger = nullptr;

// ����
SceneManager::SceneManager() {

}

// ����
SceneManager::~SceneManager() {

}


// ��ʼ������
void SceneManager::InitSceneManager() {
	// ʵ����
	auto handle = GetInstance();


}

// �ͷ�
void SceneManager::Release() {

}

// ��ȡ����
SceneManager* SceneManager::GetInstance() {
	if (!g_sceneManger) {
		g_sceneManger = new SceneManager();
	}
	return g_sceneManger;
}

// ����
void SceneManager::UpdateScene() {
	if (g_sceneManger) {
		
	}
}

// ����
void SceneManager::DrawScene() {
	if (g_sceneManger) {

	}
}
