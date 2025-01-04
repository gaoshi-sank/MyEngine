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
	std::string planepath = FileControl::ResPath("1.txt");
	
	PlaneFactory::BuildUIByFile(planepath.c_str(), [&](int uiType, int ui_id, int msgType, int message) {
		EventControl(uiType, ui_id, msgType, message);
	});
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
	//Scene_Base::Stop();
}

// ���UI�¼�����
void Scene_Test::EventControl(int uiType, int ui_id, int msgType, int message) {
	if (uiType == UI_Base::UIStyle_Button) {
		if (msgType == UI_Base::UIMsgType_Click) {
			SceneManager::DeleteScene(this->scene_id);
		}
	}
}