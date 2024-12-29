#include "Scene_Obejct.h"
#include "SceneManager.h"

// 构造
Scene_Obejct::Scene_Obejct() {
	// 加入管理
	SceneManager::GetInstance()->AddScene(this);
}

// 析构
Scene_Obejct::~Scene_Obejct() {

}

// 初始化
void Scene_Obejct::Init() {

}

// 释放
void Scene_Obejct::Release() {

}

// 更新
void Scene_Obejct::Update() {

}

// 渲染
void Scene_Obejct::Draw() {

}

// 停止
void Scene_Obejct::Stop() {

}
