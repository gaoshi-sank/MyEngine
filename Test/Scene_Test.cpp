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

	auto control = InputFactory::GetInstance()->GetInput();
	if (control && control->GetKeyState(VK_ESCAPE)) {
		isclick = 1;
	}
	else {
		if (isclick == 1) {
			isclick = 2;
		}
		if (isclick == 2) {
			_test->visiable = _test->visiable ? false : true;
		}
		isclick = 0;
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