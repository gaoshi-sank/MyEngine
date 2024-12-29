#include "SceneManager.h"


SceneManager* SceneManager::g_sceneManger = nullptr;

// ����
SceneManager::SceneManager() {
	// ��������
	Scene_Index = 0;		// ��������

}

// ����
SceneManager::~SceneManager() {

}


// ��ʼ������
void SceneManager::InitSceneManager() {
	// ʵ����
	auto handle = GetInstance();
	if (handle) {

	}
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
		g_sceneManger->Update();
	}
}

// ����
void SceneManager::DrawScene() {
	if (g_sceneManger) {
		g_sceneManger->Draw();
	}
}

// ���볡��
void SceneManager::AddScene(Scene_Base* _scene) {
	if (_scene) {
		bool isnone = true;
		for (auto& mapping : MapScene) {
			auto& scene = mapping.second;
			if (scene == _scene) {
				isnone = false;
				break;
			}
		}
		if (isnone) {
			MapScene[_scene->scene_id] = _scene;
		}
	}
}

// �л�����
void SceneManager::SwitchScene(unsigned int scene_id) {
	if (MapScene.count(scene_id) == 1) {
		MapScene[Scene_Index]->Stop();		// ����ֹͣ
		MapScene[Scene_Index]->Release();	// �����ͷ�
		Scene_Index = scene_id;
	}
}

// ɾ������
void SceneManager::DeleteScene(unsigned int scene_id) {
	if (MapScene.count(scene_id) == 1) {
		// ɾ����ǰ����
		MapScene[scene_id]->Stop();
		MapScene[scene_id]->Release();

		// ɾ���ǵ�ǰ���� - scene�滻
		if (scene_id == Scene_Index) {
			for (auto& mapping : MapScene) {
				auto& scene = mapping.second;
				if (scene->scene_id != scene_id) {
					Scene_Index = scene->scene_id;
					break;
				}
			}
		}
	}
}

// ����
void SceneManager::Update() {
	if (Scene_Index != 0 && MapScene.count(Scene_Index) == 1) {
		auto& scene = MapScene[Scene_Index];
		scene->Update();
	}
}

// ��Ⱦ
void SceneManager::Draw(){
	if (Scene_Index != 0 && MapScene.count(Scene_Index) == 1) {
		auto& scene = MapScene[Scene_Index];
		scene->Draw();
	}
}