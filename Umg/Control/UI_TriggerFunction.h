#ifndef _UI_TriggerFunction_h_
#define _UI_TriggerFunction_h_

#include "../UI_Base.h"

// ���ڴ����ص�����
class UI_TriggerFunction {
public:
	// �¼��ص�ָ��
	std::function<void(int* _param)> callback_hover;	// ��ͣ�ص�
	std::function<void(int* _param)> callback_down;		// ���»ص�
	std::function<void(int* _param)> callback_up;		// �ſ��ص�
	std::function<void(int* _param)> callback_click;	// ����ص�

public:
	// ����
	UI_TriggerFunction() = default;

	// ����
	~UI_TriggerFunction() = default;

	// ���ûص� - ��ͣ
	virtual void Event_Hover(std::function<void(int* _param)> _hover) = 0;

	// ���ûص� - ����
	virtual void Event_Down(std::function<void(int* _param)> _down) = 0;

	// ���ûص� - �ſ�
	virtual void Event_Up(std::function<void(int* _param)> _up) = 0;

	// ���ûص� - ���
	virtual void Event_Click(std::function<void(int* _param)> _hover) = 0;

};




#endif // !_UI_TriggerFunction_h_

