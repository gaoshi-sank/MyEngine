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
	std::string testpath = "C:\\Users\\asus\\Pictures\\39\\Common\\9-1.png";
	
	_test = new UI_Plane();
	if (_test) {
		_test->SetLocation(0, 0);
		_test->SetSize(200, 50);

		UI_Button* att1 = new UI_Button();
		if (att1) {
			att1->Create(testpath.c_str(), 0, 0, 100, 50);
			_test->AddAttachedUI(att1);
		}
		
		UI_Button* att2 = new UI_Button();
		if (att2) {
			att2->Create(testpath.c_str(), 100, 0, 100, 50);
			_test->AddAttachedUI(att2);
		}
	}
	
}

// 释放
void Scene_Test::Release() {

}

// 更新
void Scene_Test::Update() {



}

// 渲染
void Scene_Test::Draw() {



}

// 停止
void Scene_Test::Stop() {

}