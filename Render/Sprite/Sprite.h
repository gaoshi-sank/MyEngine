#ifndef _Sprite_h_
#define _Sprite_h_

#include "../Render.h"

// 精灵类
class Sprite {
private:
	void* _image;	// 图像对象
	float opacity;	// 不透明度
	float angle;	// 旋转角度
	int draw_x, draw_y, draw_width, draw_height;	// 绘制区
	int src_x, src_y, src_width, src_height;		// 资源裁剪区


public:
	// 构造
	Sprite();

	// 析构
	~Sprite();

	// 创建
	void SetImage(const char* filename = nullptr);

	// 更新
	void Update();

	// 绘制
	void Draw();

};



#endif // !_Sprite_h_
