#include "Sprite.h"
#include "../RenderFactory.h"
#include "../Direct2D/Render_Direct2d.h"

// ���ֽ�תΪ���ַ� 
static bool CharToWChar(const char* szStr, WCHAR* wszClassName) {
	bool result = false;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// ת�� 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}
	return result;
}

// ����
Sprite::Sprite() {
	// ͼ������
	_image = nullptr;
	opacity = 1.0f;
	angle = 0.0f;
	src_x = src_y = src_width = src_height = 0;


	// �ı�����
	text = "";					// ����
	render_text = nullptr;		// ��Ⱦ������
	font_size = 18.0f;			// ���ִ�С
	text_format = nullptr;		// ���ָ�ʽ
	text_layout = nullptr;		// �ı����� 
	text_brash = nullptr;		// ���ӻ�ˢ 
	memset(text_color, 0, sizeof(int) * 3);	// ��ˢ��ɫ
	max_fontlength = 1024;		// �ɻ����ı�����
	text_HorizontalStyle = 1;	// �ı�ˮƽ���
	text_VerticalStyle = 1;		// �ı���ֱ���
	text_swrapping = 0;			// ���и�ʽ

	// ������
	draw_x = draw_y = draw_width = draw_height = 0;

}

// ����
Sprite::~Sprite() {

	if (_image) {
		delete _image;
		_image = nullptr;
	}

}

// ����ͼ��
void Sprite::SetImage(const char* filename) {
	auto render = RenderFactory::GetInstance()->GetRender();
	if (filename && render && !this->_image) {
		this->_image = render->CreateImage(filename);

		// Ĭ��ȫ��һ����ƣ������ü�
		render->GetImageSize(this->_image, src_width, src_height);
		draw_width = draw_x + src_width;
		draw_height = draw_y + src_height;
	}
}

// �����ı�
void Sprite::SetText(const std::string& _text) {
	// ���������ı�
	this->text.clear();
	this->text = _text;
	if (this->render_text) {
		delete this->render_text;
		this->render_text = nullptr;
	}

	// �ֽ�ת��
	size_t loopnum = text.size() / limit_length;
	this->render_text = new wchar_t[limit_length * (loopnum + 1)];
	memset(this->render_text, '\0', sizeof(wchar_t) * (limit_length * (loopnum + 1)));
	CharToWChar(this->text.c_str(), this->render_text);

	// �����ı�����
	
}

// ����
void Sprite::Update() {

}

// ����
void Sprite::Draw() {

	if (_image) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			// ͼ�����
			render->RenderImage(_image, draw_x, draw_y, draw_width, draw_height, src_x, src_y, src_width, src_height, opacity, angle);

			// ͼ�λ���

			// ��������

			// �ı�����

		}
	}

}

// ����ͼ��
void Sprite::DrawImage() {

}

// ��������ͼ��
void Sprite::DrawFigure() {

}

// ������������
void Sprite::DrawLine() {

}

// ���������ı�
void Sprite::DrawText() {

}