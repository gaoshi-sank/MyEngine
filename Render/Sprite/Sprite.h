#ifndef _Sprite_h_
#define _Sprite_h_

#include "../Render.h"	// 渲染器
#include <iostream>		// 标准组件

const int limit_length = 1024;

// 精灵类
class Sprite {
private:
	// 图像
	void* _image;				// 图像对象
	float opacity;				// 不透明度
	float angle;				// 旋转角度
	int src_x, src_y, 
		src_width, src_height;	// 资源裁剪区

	// 文本
	std::string text;			// 文字
	wchar_t* render_text;		// 渲染用
	float font_size;			// 文字大小
	void* text_format;			// 文字格式
	void* text_layout;			// 文本布局 
	void* text_brash;			// 底子画刷 
	int text_color[3];			// 画刷颜色
	int max_fontlength;			// 可绘制文本长度
	int text_HorizontalStyle;	// 文本水平风格 - 1 默认居中
	int text_VerticalStyle;		// 文本垂直风格 - 1 默认居中
	int text_swrapping;			// 换行格式

	// 绘制区
	int draw_x, draw_y, draw_width, draw_height;

public:
	// 构造
	Sprite();

	// 析构
	~Sprite();

	// 创建图像
	void SetImage(const char* filename = nullptr);

	// 创建文本
	void SetText(const std::string& _text);

	// 更新
	void Update();

	// 绘制
	// 图像、图形、线条、文本
	void Draw();

	// 单独绘制图像
	void DrawImage();

	// 单独绘制图形
	void DrawFigure();

	// 单独绘制线条
	void DrawLine();

	// 单独绘制文本
	void DrawText();

};



#endif // !_Sprite_h_
