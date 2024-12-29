#include "Scene_Test.h"

// 构造
Scene_Test::Scene_Test() {
	_test = nullptr;


}

// 析构
Scene_Test::~Scene_Test() {

}

// 初始化
void Scene_Test::Init() {
	std::string testpath = "C:\\Users\\asus\\Pictures\\39\\Title\\1-1.bmp";
	_test = new SImage(testpath.c_str());
	if (_test) {
		_test->SetLocaiton(0, 0);
		//_test->SetSize(400, 300);
	}
}

// 释放
void Scene_Test::Release() {

}

// 更新
void Scene_Test::Update() {
	if (!isinit) {
		isinit = true;
		Init();
	}
	
	if (_test) {
		_test->Update();
	}

}

// 渲染
void Scene_Test::Draw() {

	if (_test) {
		_test->Draw();
	}

}

// 停止
void Scene_Test::Stop() {

}