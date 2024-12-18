#ifndef _Render_Direct2d_h_
#define _Render_Direct2d_h_

// 父类文件
#include "../Render.h"

// 渲染包含库
#include <wincodec.h>						// WIC组件
#include <d2d1.h>							// 2d
#include <dwrite.h>							// 文字
#include <d2d1helper.h>		


// 渲染静态库
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"windowscodecs.lib")


// 具体渲染类
// Direct2D API
class Render_Direct2d : public Render {
private:
	IWICImagingFactory* WicFactory = nullptr;		// WIC工厂
	ID2D1Factory* factory;							// 渲染工厂
	ID2D1HwndRenderTarget* render_target;			// 渲染画刷
	IDWriteFactory* textfactory;					// 文字工厂

public:
	// 构造
	Render_Direct2d();

	// 析构
	virtual ~Render_Direct2d();

	// 创建渲染器
	virtual bool BuildRender(HWND hwnd, int width, int height);

	// 释放 渲染器
	virtual void Release();

	// 创建图像
	virtual ID2D1Bitmap* CreateImage(const char* filename);

private:
	// 获取图像格式解析对象
	HRESULT GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename);

};


#endif // !_Render_Direct2d_h_