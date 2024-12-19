#include "Sprite.h"
#include "../RenderFactory.h"
#include "../Direct2D/Render_Direct2d.h"

// ����
Sprite::Sprite() {
	_image = nullptr;
	draw_x = draw_y = draw_width = draw_height = 0;
	src_x = src_y = src_width = src_height = 0;
	opacity = 1.0f;
	angle = 0.0f;
}

// ����
Sprite::~Sprite() {

	if (_image) {
		delete _image;
		_image = nullptr;
	}

}

// ����
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

// ����
void Sprite::Update() {

}

// ����
void Sprite::Draw() {

	if (_image) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			render->RenderImage(_image, draw_x, draw_y, draw_width, draw_height, src_x, src_y, src_width, src_height, opacity, angle);
		}
	}

}