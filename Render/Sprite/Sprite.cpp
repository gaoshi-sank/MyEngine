#include "Sprite.h"
#include "../RenderFactory.h"
#include "../Direct2D/Render_Direct2d.h"

// 多字节转为宽字符 
static bool CharToWChar(const char* szStr, WCHAR* wszClassName) {
	bool result = false;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// 转换 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}
	return result;
}

// 构造
Sprite::Sprite() {
	// 图像属性
	_image = nullptr;
	opacity = 1.0f;
	angle = 0.0f;
	src_x = src_y = src_width = src_height = 0;


	// 文本属性
	text = "";					// 文字
	render_text = nullptr;		// 渲染用文字
	font_size = 18.0f;			// 文字大小
	text_format = nullptr;		// 文字格式
	text_layout = nullptr;		// 文本布局 
	text_brash = nullptr;		// 底子画刷 
	memset(text_color, 0, sizeof(int) * 3);	// 画刷颜色
	max_fontlength = 1024;		// 可绘制文本长度
	text_HorizontalStyle = 1;	// 文本水平风格
	text_VerticalStyle = 1;		// 文本垂直风格
	text_swrapping = 0;			// 换行格式

	// 绘制区
	draw_x = draw_y = draw_width = draw_height = 0;

}

// 析构
Sprite::~Sprite() {

	if (_image) {
		delete _image;
		_image = nullptr;
	}

}

// 创建图像
void Sprite::SetImage(const char* filename) {
	auto render = RenderFactory::GetInstance()->GetRender();
	if (filename && render && !this->_image) {
		this->_image = render->CreateImage(filename);

		// 默认全部一起绘制，不做裁剪
		render->GetImageSize(this->_image, src_width, src_height);
		draw_width = draw_x + src_width;
		draw_height = draw_y + src_height;
	}
}

// 创建文本
void Sprite::SetText(const std::string& _text) {
	// 重新设置文本
	this->text.clear();
	this->text = _text;
	if (this->render_text) {
		delete this->render_text;
		this->render_text = nullptr;
	}

	// 字节转换
	size_t loopnum = text.size() / limit_length;
	this->render_text = new wchar_t[limit_length * (loopnum + 1)];
	memset(this->render_text, '\0', sizeof(wchar_t) * (limit_length * (loopnum + 1)));
	CharToWChar(this->text.c_str(), this->render_text);

	// 重设文本布局
	
}

// 更新
void Sprite::Update() {

}

// 绘制
void Sprite::Draw() {

	if (_image) {
		auto render = RenderFactory::GetInstance()->GetRender();
		if (render) {
			// 图像绘制
			render->RenderImage(_image, draw_x, draw_y, draw_width, draw_height, src_x, src_y, src_width, src_height, opacity, angle);

			// 图形绘制

			// 线条绘制

			// 文本绘制

		}
	}

}

// 绘制图像
void Sprite::DrawImage() {

}

// 单独绘制图形
void Sprite::DrawFigure() {

}

// 单独绘制线条
void Sprite::DrawLine() {

}

// 单独绘制文本
void Sprite::DrawText() {

}