#ifndef _UI_Lable_h_
#define _UI_Lable_h_

#include "../UI_Base.h"

// ��ǩUI
class UI_Lable : private UI_Base {
private:

public:
	// ����
	UI_Lable();

	// ����
	~UI_Lable();

	// �¼�����
	virtual void CheckEvent(int* param);

	// ����
	virtual void Update();

	// ����
	virtual void Draw();

	// ����λ��
	virtual void SetLocation(int x, int y);

	// ���ô�С
	virtual void SetSize(int x, int y);

	// ���ÿɼ���
	virtual void SetVisiable(bool life);
};


#endif //!_UI_Lable_h_