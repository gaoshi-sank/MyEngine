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
	// ���� 
	ID2D1Factory* factory;							// ��Ⱦ����
	ID2D1HwndRenderTarget* render_target;			// ��Ⱦ��ˢ
	IWICImagingFactory* WicFactory = nullptr;		// WIC����
	IDWriteFactory* textfactory;					// ���ֹ���

public:


};


#endif // !_Render_Direct2d_h_