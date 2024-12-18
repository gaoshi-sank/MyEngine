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
	// 工具 
	ID2D1Factory* factory;							// 渲染工厂
	ID2D1HwndRenderTarget* render_target;			// 渲染画刷
	IWICImagingFactory* WicFactory = nullptr;		// WIC工厂
	IDWriteFactory* textfactory;					// 文字工厂

public:


};


#endif // !_Render_Direct2d_h_