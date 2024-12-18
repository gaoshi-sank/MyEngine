#ifndef _Render_Direct2d_h_
#define _Render_Direct2d_h_

// �����ļ�
#include "../Render.h"

// ��Ⱦ������
#include <wincodec.h>						// WIC���
#include <d2d1.h>							// 2d
#include <dwrite.h>							// ����
#include <d2d1helper.h>		


// ��Ⱦ��̬��
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"windowscodecs.lib")


// ������Ⱦ��
// Direct2D API
class Render_Direct2d : public Render {
private:
	IWICImagingFactory* WicFactory = nullptr;		// WIC����
	ID2D1Factory* factory;							// ��Ⱦ����
	ID2D1HwndRenderTarget* render_target;			// ��Ⱦ��ˢ
	IDWriteFactory* textfactory;					// ���ֹ���

public:
	// ����
	Render_Direct2d();

	// ����
	virtual ~Render_Direct2d();

	// ������Ⱦ��
	virtual bool BuildRender(HWND hwnd, int width, int height);

	// �ͷ� ��Ⱦ��
	virtual void Release();

	// ����ͼ��
	virtual ID2D1Bitmap* CreateImage(const char* filename);

private:
	// ��ȡͼ���ʽ��������
	HRESULT GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename);

};


#endif // !_Render_Direct2d_h_