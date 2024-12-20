#ifndef _UIFactory_h_
#define _UIFactory_h_

#include <iostream>
#include <mutex>
#include <vector>
#include "Control/UI_Lable.h"		// ��ǩUI


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

	// ����
	static void Update();

	// ��Ⱦ
	static void Draw();

	// �ж϶���
	static bool GetLevelTop(int pos_x, int pos_y, UI_Base* other);


#endif // !_UIFactory_h_