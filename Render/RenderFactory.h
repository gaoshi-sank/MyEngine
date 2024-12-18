#ifndef _Render_h_
#define _Render_h_

#include <iostream>



// 渲染工厂
class RenderFactory {
private:
	RenderFactory();
	~RenderFactory();

	// 属性
	int renderType;

	// 静态值
	static RenderFactory* g_renderFactory;

public:
	static void InitRender(int renderType);
	static RenderFactory* GetInstance();
	static void Release();

};



#endif // !_Render_h_