#ifndef _Render_h_
#define _Render_h_

#include <Windows.h>

// ³éÏóäÖÈ¾Àà
class Render {
public:
	Render() = default;
	virtual ~Render() = default;
	virtual bool BuildRender(HWND hwnd, int width, int height) = 0;
	virtual void Release() = 0;
	virtual void BeginPlay() = 0;
	virtual void EndPlay() = 0;
};

#endif // !_Render_h_


