#ifndef _Render_h_
#define _Render_h_

#include <Windows.h>

// ³éÏóäÖÈ¾Àà
class Render {
public:
	Render();

	virtual ~Render();

	virtual bool BuildRender(HWND hwnd, int width, int height) = 0;
	

};

#endif // !_Render_h_


