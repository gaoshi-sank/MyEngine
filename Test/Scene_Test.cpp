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
	_test = PlaneFactory::BuildOnePlane(planepath.c_str());
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