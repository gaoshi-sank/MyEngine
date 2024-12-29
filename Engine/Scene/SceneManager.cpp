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
		handle->Init();
	}
}

// �ͷ�
void SceneManager::ReleaseScene() {
	if (g_sceneManger) {
		g_sceneManger->Update();
	}
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
void SceneManager::AddScene(Scene_Obejct* _scene) {
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
			_scene->Init();								// ��ʼ��
			Scene_Index = _scene->scene_id;				// ����ӳ��
			MapScene[_scene->scene_id] = _scene;		// ����
		}
	}
}

// �л�����
void SceneManager::SwitchScene(unsigned int scene_id) {
	if (MapScene.count(scene_id) == 1) {
		MapScene[Scene_Index]->Stop();		// ����ֹͣ
		MapScene[Scene_Index]->Release();	// �����ͷ�
		delete MapScene[Scene_Index];		// �ͷ��ڴ�
		MapScene[Scene_Index] = nullptr;	// �ÿ�
		Scene_Index = scene_id;
	}
}

// ɾ������
void SceneManager::DeleteScene(unsigned int scene_id) {
	if (MapScene.count(scene_id) == 1) {
		// ɾ����ǰ����
		MapScene[Scene_Index]->Stop();		// ����ֹͣ
		MapScene[Scene_Index]->Release();	// �����ͷ�
		delete MapScene[Scene_Index];		// �ͷ��ڴ�
		MapScene[Scene_Index] = nullptr;	// �ÿ�

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

// ��ʼ��
void SceneManager::Init() {

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

// �ͷ�
void SceneManager::Release() {

}