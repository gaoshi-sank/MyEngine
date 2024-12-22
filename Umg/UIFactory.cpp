#include "UIFactory.h"

static UIFactory* g_uiFactory = nullptr;

// 构造
UIFactory::UIFactory() {

}

// 析构
UIFactory::~UIFactory() {

}


// 初始化
void UIFactory::InitUIProvider() {
	if (!g_uiFactory) {
		g_uiFactory = new UIFactory();
	}
}

// 释放
void UIFactory::Release() {

}

// 添加控件
void UIFactory::AddWindow(UI_Base* _ui) {

}

// 删除控件
void UIFactory::DelWindow(UI_Base* _ui) {

}

// 更新
void UIFactory::Update() {

}

// 渲染
void UIFactory::Draw() {

}

// 判断顶层
bool UIFactory::GetLevelTop(int pos_x, int pos_y, UI_Base* other) {


	return false;
}