#include "Scene_Test.h"

// ����
Scene_Test::Scene_Test() {
	_test = nullptr;


}

// ����
Scene_Test::~Scene_Test() {

}

// ��ʼ��
void Scene_Test::Init() {
	std::string testpath = "C:\\Users\\asus\\Pictures\\39\\Title\\1-1.bmp";
	_test = new SImage(testpath.c_str());
	if (_test) {
		_test->SetLocaiton(0, 0);
		//_test->SetSize(400, 300);
	}
}

// �ͷ�
void Scene_Test::Release() {

}

// ����
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

// ��Ⱦ
void Scene_Test::Draw() {

	if (_test) {
		_test->Draw();
	}

}

// ֹͣ
void Scene_Test::Stop() {

}