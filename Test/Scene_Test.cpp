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

// �ͷ�
void Scene_Test::Release() {

}

// ����
void Scene_Test::Update() {



}

// ��Ⱦ
void Scene_Test::Draw() {



}

// ֹͣ
void Scene_Test::Stop() {

}