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
	std::string planepath = FileControl::ResPath("1.txt");
	_test = PlaneFactory::BuildOnePlane(planepath.c_str());
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