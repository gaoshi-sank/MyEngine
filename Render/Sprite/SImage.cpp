#include "SImage.h"
#include "SpriteHelper.h"
#include "../RenderFactory.h"
#include "../Direct2D/Render_Direct2d.h"

// 构造
SImage::SImage() {
	// 绘制区
	draw_x = draw_y = draw_width = draw_height = 0;

	// 图像属性
	_image = nullptr;
	opacity = 1.0f;
	angle = 0.0f;
	src_x = src_y = src_width = src_height = 0;

}

// 构造
SImage::SImage(const char* filename) : SImage(){
	auto render = RenderFactory::GetInstance()->GetRender();
	if (filename && render && !this->_image) {
		// 创建图像句柄
		this->_image = render->CreateImage(filename);

		// 默认
		render->GetImageSize(this->_image, src_width, src_height);
		draw_width = draw_x + src_width;
		draw_height = draw_y + src_height;
	}
}

// 析构
SImage::~SImage() {
	if (_image) {
		delete _image;
		_image = nullptr;
	}

}

// 更新
void SImage::Update() {

}

// 绘制图像
void SImage::Draw() {
	if (_image) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			render->RenderImage(_image, draw_x, draw_y, draw_width, draw_height, src_x, src_y, src_width, src_height, opacity, angle);
		}
	}
}

// 设置绘制位置
void SImage::SetLocaiton(int x, int y) {
	this->draw_x = x;
	this->draw_y = y;
}

// 设置绘制大小
void SImage::SetSize(int w, int h) {
	this->draw_width = w;
	this->draw_height = h;
}