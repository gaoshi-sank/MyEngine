#include "UIFactory.h"

static UIFactory* g_uiFactory = nullptr;

// ����
UIFactory::UIFactory() {

}

// ����
UIFactory::~UIFactory() {

}


// ��ʼ��
void UIFactory::InitUIProvider() {
	if (!g_uiFactory) {
		g_uiFactory = new UIFactory();
	}
}

// �ͷ�
void UIFactory::Release() {

}

// ��ӿؼ�
void UIFactory::AddWindow(UI_Base* _ui) {

}

// ɾ���ؼ�
void UIFactory::DelWindow(UI_Base* _ui) {

}

// ����
void UIFactory::Update() {

}

// ��Ⱦ
void UIFactory::Draw() {

}

// �ж϶���
bool UIFactory::GetLevelTop(int pos_x, int pos_y, UI_Base* other) {


	return false;
}