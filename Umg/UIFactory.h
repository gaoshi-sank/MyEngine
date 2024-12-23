#ifndef _UIFactory_h_
#define _UIFactory_h_

#include "../EngineManager/EngineConfig.h"
#include "Control/UI_Lable.h"		// ��ǩUI
#include "Control/UI_Button.h"		// ��ťUI


// UI����
class UIFactory {
private:
	// ��
	std::mutex lockList;
	std::mutex lockAddlist;
	std::mutex lockDellist;

	// UI�б�
	std::vector<UI_Base*> list;
	std::vector<UI_Base*> addList;
	std::vector<UI_Base*> delList;

	// ����
	UIFactory();

	// ����
	~UIFactory();

public:
	// ��ʼ��
	static void InitUIProvider();

	// �ͷ�
	static void Release();

	// ��ӿؼ�
	static void AddWindow(UI_Base* _ui);

	// ɾ���ؼ�
	static void DelWindow(UI_Base* _ui);

	// �¼�����
	static void CheckEvent(unsigned int* param);

	// ����
	static void Update();

	// ��Ⱦ
	static void Draw();

	// �ж϶���
	static bool GetLevelTop(int pos_x, int pos_y, UI_Base* other);

private:

};

#endif // !_UIFactory_h_
