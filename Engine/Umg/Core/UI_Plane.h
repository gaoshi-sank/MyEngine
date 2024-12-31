#ifndef _UI_Plane_h_
#define _UI_Plane_h_


#include "../Control/UI_Lable.h"		// ��ǩUI
#include "../Control/UI_Button.h"		// ��ťUI
#include "../Control/UI_CheckBox.h"		// ��ťUI


// �����
// һ�����ڷ�������UI�ؼ�
class UI_Plane : public UI_Base {
private:
	std::vector<UI_Base*> ListAttached;	// ����UI�б�
	std::mutex lockList;

public:
	// ����
	UI_Plane();

	// ����
	virtual ~UI_Plane();

	// Ԥ�ͷ�
	virtual void PreRelease();

	// ����
	virtual bool Create();

	// ���븽��UI
	virtual void AddAttachedUI(UI_Base* _ui);

	// �¼�����
	virtual void CheckEvent(unsigned int* param);

	// ����
	virtual void Update();

	// ����
	virtual void Draw();

	// ����λ��
	virtual void SetLocation(int x, int y);

	// ���ô�С
	virtual void SetSize(int w, int h);

	// ���ÿɼ���
	virtual void SetVisiable(bool visible = false);

};


#endif // !_UI_Plane_h_
