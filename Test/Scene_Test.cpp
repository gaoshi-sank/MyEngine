#include "Scene_Test.h"
#include "../Engine/Input/InputFactory.h"

// 构造
Scene_Test::Scene_Test() {
	_test = nullptr;
}

// 析构
Scene_Test::~Scene_Test() {

	for (auto& _ui : listTest) {
		if (_ui) {
			_ui->PreRelease();
			_ui = nullptr;
		}
	}
	listTest.clear();

}

// 初始化
void Scene_Test::Init() {
	std::string testpath = "C:\\Users\\asus\\Pictures\\39\\Common\\9-1.png";
	std::string planepath = FileControl::ResPath("1.txt");
	
	listTest = PlaneFactory::BuildUIByFile(planepath.c_str(), [&](int uiType, int ui_id, int msgType, int message) {
		EventControl(uiType, ui_id, msgType, message);
	});

	LogI("request:[%d]", 1);
	LogI("request:[%d]", 2);

	for (auto i = 0; i < 10000;i++) {
		LogI("logsystem testing...");
	}
}

// 释放
void Scene_Test::Release() {

	

}

// 更新
void Scene_Test::Update() {
	auto input = InputFactory::GetInstance()->GetInput();
	if (input) {
		auto x = -1, y = -1;
		auto ret = input->GetMousePos(x, y);
		if (ret && (x != -1 && y != -1)) {
			LogI("mouse pos = [%d,%d]", x, y);
		}
	}

}

// 渲染
void Scene_Test::Draw() {



}

// 停止
void Scene_Test::Stop() {
	Scene_Base::Stop();
}


// 面板UI事件处理
void Scene_Test::EventControl(int uiType, int ui_id, int msgType, int message) {
	if (uiType == UI_Base::UIStyle_Button) {
		if (msgType == UI_Base::UIMsgType_Click) {
			SceneManager::DeleteScene(this->scene_id);
		}
	}
}