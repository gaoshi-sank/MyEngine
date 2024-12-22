#include "UI_Base.h"

static unsigned int baseid = 0x00;

// ����
UI_Base::UI_Base() {
	// ��������
	this->window_id = ++baseid;				// ���ڱ�� 
	this->window_style = 0x00;				// �������� 
	this->window_visible = true;			// Ĭ�� - �ɼ�
	this->window_release = false;			// Ĭ�� - δ�ͷ�
	this->window_key = false;				// Ĭ�� - ���������� 
	this->window_mouse = true;				// Ĭ�� - �ɴ������ 
	this->window_renderlevel = 0x00;		// Ĭ�� - ��Ⱦ�� 0

	// �¼�����
	mouse_posx = mouse_posy = 0;
	window_inrect = false;
	
	// ��������
	this->window_x = this->window_y = this->window_width = this->window_height = 0;
}

// ����
UI_Base::~UI_Base() {

}