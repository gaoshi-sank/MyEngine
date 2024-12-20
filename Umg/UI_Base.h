#ifndef _UI_Base_h_
#define _UI_Base_h_

// �����ļ�
#include "../Render/Sprite/SSprite.h"	// ��Ⱦ�þ���

// �ؼ�
class UI_Base {
public:
	// ��������
	unsigned int window_id;		// ���ڱ�� 
	unsigned int window_style;	// �������� 
	bool window_visible;		// �ɼ���
	bool window_release;		// �ͷ���
	bool window_key;			// �ɴ��������¼� 
	bool window_mouse;			// �ɴ�������¼�
	int window_renderlevel;		// ������Ⱦ��
	int window_x;				// �������� X
	int window_y;
	int window_width;			
	int window_height;			// �������� height

public:
	// ����
	UI_Base();

	// ����
	virtual ~UI_Base();

	// �¼�����
	virtual void CheckEvent(int* param) = 0;

	// ����
	virtual void Update() = 0;

	// ����
	virtual void Draw() = 0;

	// ����λ��
	virtual void SetLocation(int x, int y) = 0;

	// ���ô�С
	virtual void SetSize(int x, int y) = 0;

	// ���ÿɼ���
	virtual void SetVisiable(bool life) = 0;
};


#endif //!_UI_Base_h_