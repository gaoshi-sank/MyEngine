#ifndef _Render_h_
#define _Render_h_

#include <iostream>



// ��Ⱦ����
class RenderFactory {
private:
	RenderFactory();
	~RenderFactory();

	// ����
	int renderType;

	// ��ֵ̬
	static RenderFactory* g_renderFactory;

public:
	static void InitRender(int renderType);
	static RenderFactory* GetInstance();
	static void Release();

};



#endif // !_Render_h_