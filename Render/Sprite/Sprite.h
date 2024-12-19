#ifndef _Sprite_h_
#define _Sprite_h_

#include "../Render.h"	// ��Ⱦ��
#include <iostream>		// ��׼���

const int limit_length = 1024;

// ������
class Sprite {
private:
	// ͼ��
	void* _image;				// ͼ�����
	float opacity;				// ��͸����
	float angle;				// ��ת�Ƕ�
	int src_x, src_y, 
		src_width, src_height;	// ��Դ�ü���

	// �ı�
	std::string text;			// ����
	wchar_t* render_text;		// ��Ⱦ��
	float font_size;			// ���ִ�С
	void* text_format;			// ���ָ�ʽ
	void* text_layout;			// �ı����� 
	void* text_brash;			// ���ӻ�ˢ 
	int text_color[3];			// ��ˢ��ɫ
	int max_fontlength;			// �ɻ����ı�����
	int text_HorizontalStyle;	// �ı�ˮƽ��� - 1 Ĭ�Ͼ���
	int text_VerticalStyle;		// �ı���ֱ��� - 1 Ĭ�Ͼ���
	int text_swrapping;			// ���и�ʽ

	// ������
	int draw_x, draw_y, draw_width, draw_height;

public:
	// ����
	Sprite();

	// ����
	~Sprite();

	// ����ͼ��
	void SetImage(const char* filename = nullptr);

	// �����ı�
	void SetText(const std::string& _text);

	// ����
	void Update();

	// ����
	// ͼ��ͼ�Ρ��������ı�
	void Draw();

	// ��������ͼ��
	void DrawImage();

	// ��������ͼ��
	void DrawFigure();

	// ������������
	void DrawLine();

	// ���������ı�
	void DrawText();

};



#endif // !_Sprite_h_
