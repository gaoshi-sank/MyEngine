#include "SceneManager.h"


SceneManager* SceneManager::g_sceneManger = nullptr;

// 构造
SceneManager::SceneManager() {
	// 基础属性
	Scene_Index = 0;		// 场景索引

}

// 析构
SceneManager::~SceneManager() {

}


// 初始化引擎
void SceneManager::InitSceneManager() {
	// 实例化
	auto handle = GetInstance();
	if (handle) {

	}
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
		g_sceneManger->Update();
	}
}

// 绘制
void SceneManager::DrawScene() {
	if (g_sceneManger) {
		g_sceneManger->Draw();
	}
}

// 加入场景
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

// 切换场景
void SceneManager::SwitchScene(unsigned int scene_id) {
	if (MapScene.count(scene_id) == 1) {
		MapScene[Scene_Index]->Stop();		// 场景停止
		MapScene[Scene_Index]->Release();	// 场景释放
		Scene_Index = scene_id;
	}
}

// 删除场景
void SceneManager::DeleteScene(unsigned int scene_id) {
	if (MapScene.count(scene_id) == 1) {
		// 删除当前场景
		MapScene[scene_id]->Stop();
		MapScene[scene_id]->Release();

		// 删除是当前场景 - scene替换
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

// 更新
void SceneManager::Update() {
	if (Scene_Index != 0 && MapScene.count(Scene_Index) == 1) {
		auto& scene = MapScene[Scene_Index];
		scene->Update();
	}
}

// 渲染
void SceneManager::Draw(){
	if (Scene_Index != 0 && MapScene.count(Scene_Index) == 1) {
		auto& scene = MapScene[Scene_Index];
		scene->Draw();
	}
}