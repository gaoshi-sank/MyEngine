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
void SceneManager::AddScene(Scene_Base* _scene) {
	if (_scene && g_sceneManger) {
		bool isnone = true;
		for (auto& mapping : g_sceneManger->MapScene) {
			auto& scene = mapping.second;
			if (scene == _scene) {
				isnone = false;
				break;
			}
		}
		if (isnone) {
			_scene->Init();											// ��ʼ��
			g_sceneManger->Scene_Index = _scene->scene_id;			// ����ӳ��
			g_sceneManger->MapScene[_scene->scene_id] = _scene;		// ����
		}
	}
}

// �л�����
void SceneManager::SwitchScene(unsigned int scene_id) {
	if (g_sceneManger->MapScene.count(scene_id) == 1) {
		 g_sceneManger->MapScene[ g_sceneManger->Scene_Index]->Stop();		// ����ֹͣ
		 g_sceneManger->MapScene[ g_sceneManger->Scene_Index]->Release();	// �����ͷ�
		delete  g_sceneManger->MapScene[g_sceneManger->Scene_Index];		// �ͷ��ڴ�
		g_sceneManger->MapScene[g_sceneManger->Scene_Index] = nullptr;		// �ÿ�
		g_sceneManger->Scene_Index = scene_id;
	}
}

// ɾ������
void SceneManager::DeleteScene(unsigned int scene_id) {
	if (g_sceneManger->MapScene.count(scene_id) == 1) {
		// ɾ����ǰ����
		g_sceneManger->MapScene[g_sceneManger->Scene_Index]->Stop();		// ����ֹͣ
		g_sceneManger->MapScene[g_sceneManger->Scene_Index]->Release();		// �����ͷ�
		delete  g_sceneManger->MapScene[g_sceneManger->Scene_Index];		// �ͷ��ڴ�
		g_sceneManger->MapScene[g_sceneManger->Scene_Index] = nullptr;		// �ÿ�

		// ɾ���ǵ�ǰ���� - scene�滻
		if (scene_id == g_sceneManger->Scene_Index) {
			for (auto& mapping : g_sceneManger->MapScene) {
				auto& scene = mapping.second;
				if (scene->scene_id != scene_id) {
					g_sceneManger->Scene_Index = scene->scene_id;
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

// �ͷ�
void SceneManager::Release() {

}