#ifndef _Sprite_h_
#define _Sprite_h_

#include "../Render.h"

// ������
class Sprite {
private:
	void* _image;	// ͼ�����
	float opacity;	// ��͸����
	float angle;	// ��ת�Ƕ�
	int draw_x, draw_y, draw_width, draw_height;	// ������
	int src_x, src_y, src_width, src_height;		// ��Դ�ü���


public:
	// ����
	Sprite();

	// ����
	~Sprite();

	// ����
	void SetImage(const char* filename = nullptr);

	// ����
	void Update();

	// ����
	void Draw();

};



#endif // !_Sprite_h_
