#include "Render.h"
#include "RenderFactory.h"

static bool isInitCom = false;

// ����
Render::Render() {
	this->WicFactory = nullptr;			// WIC����
	this->factory = nullptr;			// ��Ⱦ����
	this->render_target = nullptr;		// ��Ⱦ��ˢ
	this->textfactory = nullptr;		// ���ֹ���

	// ����
	background_color = D2D1::ColorF(0, 0, 0);
}

// ����
Render::~Render() {

}

// ������Ⱦ��
bool Render::BuildRender(HWND hWnd, int width, int height) {
	// ���
	HRESULT hr = S_OK;

	// COM�����ʼ��
	if (!isInitCom) {
		hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
		hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, __uuidof(this->WicFactory), (LPVOID*)&(this->WicFactory));
		if (FAILED(hr)) {
			return false;
		}
		isInitCom = true;
	}

	// ���� ��Ⱦ����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &(factory));
	if (FAILED(hr)) {
		return false;
	}

	// ���� ��Ⱦ��ˢ
	D2D1_SIZE_U Size = D2D1::SizeU(width, height);
	hr = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, Size), &(render_target));
	if (FAILED(hr)) {
		return false;
	}

	// ���� ���ֹ���
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(textfactory), reinterpret_cast<IUnknown**>(&textfactory));
	if (FAILED(hr)) {
		return false;
	}

	// Ĭ�Ϸ���
	return true;
}

// �ͷ�
void Render::Release() {

}

// ��ʼ��Ⱦ
void Render::BeginPlay() {
	if (render_target) {
		render_target->BeginDraw();
		render_target->Clear(background_color);

	}
}

// ������Ⱦ
void Render::EndPlay() {
	if (render_target) {
		render_target->EndDraw();
	}
}

// ����ͼ��
void Render::RenderImage(ID2D1Bitmap* image, D2D1_RECT_F rect, D2D1_RECT_F src_rect, float opacity, float angle) {
	if (render_target && image) {
		render_target->DrawBitmap(image, rect, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src_rect);
	}
}

// �����ı�
void Render::RenderText(wchar_t* render_text, D2D1_RECT_F text_rect, IDWriteTextLayout* layout, ID2D1SolidColorBrush* brash) {
	if (render_target && render_text && layout && brash) {
		render_target->DrawText(render_text, UINT32(wcslen(render_text)), layout, text_rect, brash, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
}

// ����ͼ��
ID2D1Bitmap* Render::CreateImage(const char* filename) {
	// �����б�
	IWICFormatConverter* pConverter = nullptr;
	ID2D1Bitmap* pBitmap = nullptr;
	HRESULT hr = S_OK;
	wchar_t wfilename[260] = { 0 };
	bool result = 0;

	// ת���ַ�
	result = CharToWChar(filename, wfilename);
	if (result && this->render_target) {
		// ��ȡ��ʽ������
		hr = GetFormatConvert(pConverter, wfilename);

		// ����Ⱦ������һ��ͼ��
		if (SUCCEEDED(hr)) {
			hr = this->render_target->CreateBitmapFromWicBitmap(pConverter, nullptr, &pBitmap);
			if (FAILED(hr)) {
				pBitmap->Release();
				pBitmap = nullptr;
			}
		}

		// �ͷ���ʱ����
		if (pConverter) {
			pConverter->Release();
			pConverter = nullptr;
		}
		return pBitmap;
	}

	return nullptr;
}

// �����ı�����
IDWriteTextLayout* Render::CreateTextLayout(wchar_t* render_text, IDWriteTextFormat* text_format) {
	IDWriteTextLayout* _layout = nullptr;
	if (textfactory) {
		textfactory->CreateTextLayout(render_text,
			UINT32(wcslen(render_text)),
			text_format,
			0, 0,
			&_layout);
	}
	return _layout;
}

// �����ı���ʽ
IDWriteTextFormat* Render::CreateTextFormat(float font_size) {
	IDWriteTextFormat* textformat = nullptr;
	if (textfactory) {
		textfactory->CreateTextFormat(
			L"����", 
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			font_size,
			L"",
			&textformat);
	}
	return textformat;
}

// ������ˢ
ID2D1SolidColorBrush* Render::CreateBrush(D2D1_COLOR_F _color) {
	ID2D1SolidColorBrush* color_brush = nullptr;
	if (render_target) {
		render_target->CreateSolidColorBrush(_color, &color_brush);
	}
	return color_brush;
}

// �����ı����
void Render::SetTextStyle(IDWriteTextLayout* _layout, int horizontal, int vertical, int swrapping) {
	if (_layout) {
		// ˮƽ
		switch (horizontal) {
		case 1: 
		{
			// ˮƽ���� - Ĭ��
			_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			break;
		}
		case 2:
		{
			// ������������ - ���ܴ�������
			_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
			break;
		}
		case 3:	
		{
			// ˮƽ����
			_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
			break;
		}	
		default:
		{
			// ˮƽ����
			_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			break;
		}
		}

		// ��ֱ
		switch (vertical) {
		case 1: 
		{
			// �±�
			_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);	
			break;
		}
		case 2: 
		{
			// �ϱ�
			_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			break;
		}
		default: {
			// ��ֱ���� - Ĭ��
			_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);	
			break;
		}
		}

		// ����
		switch (vertical) {
		case 1: 
		{
			// ���ֿ��д�ϣ��Ա�������������ֿ�
			_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_WRAP);
			break;
		}
		case 2: 
		{
			_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_EMERGENCY_BREAK); 
			break;
		}
		case 3:
		{
			_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_WHOLE_WORD);
			break;
		}
		case 4:
		{
			_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_CHARACTER);
			break;
		}
		default: {
			// ������ͬһ��
			_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
			break;
		}
		}
	}
}

// ��ȡͼ���ʽ��������
HRESULT Render::GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename) {
	// �����б�
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	ID2D1Bitmap* pBitmap = nullptr;
	HRESULT hr = S_OK;
	int error = 0;								// ����ֵ

	// û�д��� - ��Ⱦ����
	if (error || !render_target || !WicFactory) {
		return -1;
	}

	// ����ͼ�񹤳�
	// ����������
	hr = WicFactory->CreateDecoderFromFilename(
		filename,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// ��ȡ֡����
	UINT counter;
	if ((hr = pDecoder->GetFrameCount(&counter)) != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// ��ȡָ��֡��ͼ��
	hr = pDecoder->GetFrame(0, &pFrame);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// ������ʽ
	hr = WicFactory->CreateFormatConverter(&pConverter);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// ��ʼ����ʽ
	hr = pConverter->Initialize(
		pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.f,
		WICBitmapPaletteTypeCustom
	);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// �ͷ���Դ
buildip3:
	if (pDecoder) {
		pDecoder->Release();
		pDecoder = nullptr;
	}
	if (pFrame) {
		pFrame->Release();
		pFrame = nullptr;
	}

	if ((error != 0) || hr != S_OK) {
		return -1;
	}

	return S_OK;
}
