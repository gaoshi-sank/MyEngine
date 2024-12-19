#ifndef _Render_h_
#define _Render_h_

#include <Windows.h>

// ������Ⱦ��
class Render {
public:
	// Ĭ�Ϲ��������
	Render() = default;
	virtual ~Render() = default;

	// ������Ⱦ��
	virtual bool BuildRender(HWND hwnd, int width, int height) = 0;
	
	// �ͷ���Ⱦ��
	virtual void Release() = 0;


	// ��ʼ��Ⱦ
	virtual void BeginPlay() = 0;

	// ������Ⱦ
	virtual void EndPlay() = 0;

	// ����ͼ��
	virtual void RenderImage(void* image, int dx = 0, int dy = 0, int dw = 0, int dh = 0, int sx = 0, int sy = 0, int sw = 0, int sh = 0, float opacity = 1.0f, float angle = 0.0f) = 0;

	// ����ͼ��
	virtual void* CreateImage(const char* filename) = 0;

	// ��ȡ��Ⱦ������
	virtual int GetType() = 0;

	// ��ȡͼ���С
	virtual void GetImageSize(void* image, int& width, int& height) = 0;
};

#endif // !_Render_h_


