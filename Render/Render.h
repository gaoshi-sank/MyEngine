#ifndef _Render_h_
#define _Render_h_

#include <Windows.h>

// 抽象渲染类
class Render {
public:
	// 默认构造和析构
	Render() = default;
	virtual ~Render() = default;

	// 建立渲染器
	virtual bool BuildRender(HWND hwnd, int width, int height) = 0;
	
	// 释放渲染器
	virtual void Release() = 0;


	// 开始渲染
	virtual void BeginPlay() = 0;

	// 结束渲染
	virtual void EndPlay() = 0;

	// 绘制图像
	virtual void RenderImage(void* image, int dx = 0, int dy = 0, int dw = 0, int dh = 0, int sx = 0, int sy = 0, int sw = 0, int sh = 0, float opacity = 1.0f, float angle = 0.0f) = 0;

	// 创建图像
	virtual void* CreateImage(const char* filename) = 0;

	// 获取渲染器类型
	virtual int GetType() = 0;

	// 获取图像大小
	virtual void GetImageSize(void* image, int& width, int& height) = 0;
};

#endif // !_Render_h_


