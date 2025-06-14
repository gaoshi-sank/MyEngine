#ifndef _Render_Direct2d_h_
#define _Render_Direct2d_h_

// ��Ⱦ������
#include <wincodec.h>			// WIC���
#include <d2d1.h>				// 2d
#include <dwrite.h>				// ����
#include <d2d1helper.h>			// ??
#include <windowsx.h>			// ��ȡLparam
#include "../EngineHelper.h"	// �����ú���

// ��Ⱦ��̬��
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"windowscodecs.lib")


// ��Ⱦ�� -- Direct2D 
class Render {
private:
	IWICImagingFactory* WicFactory = nullptr;		// WIC����
	ID2D1Factory* factory;							// ��Ⱦ����
	ID2D1HwndRenderTarget* render_target;			// ��Ⱦ��ˢ
	IDWriteFactory* textfactory;					// ���ֹ���

	// ����
	D2D1_COLOR_F background_color;	// ������ɫ


public:
	// ����
	Render();

	// ����
	virtual ~Render();

	// ������Ⱦ��
	virtual bool BuildRender(HWND hwnd, int width, int height);

	// �ͷ���Ⱦ��
	virtual void Release();

	// ��ʼ��Ⱦ
	virtual void BeginPlay();

	// ������Ⱦ
	virtual void EndPlay();

	// ����ͼ��
	virtual void RenderImage(ID2D1Bitmap* image, D2D1_RECT_F rect, D2D1_RECT_F src_rect, float opacity = 1.0f, float angle = 0.0f);

	// �����ı�
	virtual void RenderText(wchar_t* render_text, D2D1_RECT_F text_rect, IDWriteTextLayout* layout, ID2D1SolidColorBrush* brash);

	// ����ͼ��
	virtual ID2D1Bitmap* CreateImage(const char* filename);

	// �����ı�����
	virtual IDWriteTextLayout* CreateTextLayout(wchar_t* render_text, IDWriteTextFormat* text_format);

	// �����ı���ʽ
	virtual IDWriteTextFormat* CreateTextFormat(float font_size);

	// ������ˢ
	virtual ID2D1SolidColorBrush* CreateBrush(D2D1_COLOR_F _color);

	// �����ı����
	virtual void SetTextStyle(IDWriteTextLayout* _layout, int horizontal, int vertical, int swrapping);

private:
	// ��ȡͼ���ʽ��������
	HRESULT GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename);

};


#endif // !_Render_Direct2d_h_