#include "Scene_Test.h"
#include "../Engine/Input/InputFactory.h"

// ����
Scene_Test::Scene_Test() {
	_test = nullptr;
}

// ����
Scene_Test::~Scene_Test() {

	for (auto& _ui : listTest) {
		if (_ui) {
			_ui->PreRelease();
			_ui = nullptr;
		}
	}
	listTest.clear();

}

// ��ʼ��
void Scene_Test::Init() {
	std::string testpath = "C:\\Users\\asus\\Pictures\\39\\Common\\9-1.png";
	std::string planepath = FileControl::ResPath("1.txt");
	
	sfmlTest = std::make_shared<SImage>(testpath.c_str());
	if (sfmlTest) {
		
	}
}

// �ͷ�
void Scene_Test::Release() {

	

}

// ����
void Scene_Test::Update() {
	auto input = InputFactory::GetInstance()->GetInput();
	if (input) {
		auto x = -1, y = -1;
		auto ret = input->GetMousePos(x, y);
		if (ret && (x != -1 && y != -1)) {
			LogI("mouse pos = [%d,%d]", x, y);
		}
	}

	if (sfmlTest) {
		sfmlTest->Update();
	}

}

// ��Ⱦ
void Scene_Test::Draw() {

	if (sfmlTest) {
		sfmlTest->Draw();
	}

}

// ֹͣ
void Scene_Test::Stop() {
	Scene_Base::Stop();
}


// ���UI�¼�����
void Scene_Test::EventControl(int uiType, int ui_id, int msgType, int message) {
	if (uiType == UI_Base::UIStyle_Button) {
		if (msgType == UI_Base::UIMsgType_Click) {
			SceneManager::DeleteScene(this->scene_id);
		}
	}
}