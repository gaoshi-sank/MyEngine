#include "Render_Direct2d.h"

static bool isInitCom = false;

// ���ֽ�תΪ���ַ� 
bool CharToWChar(const char* szStr, WCHAR* wszClassName) {
	int result = 0;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// ת�� 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}

	return result;
}

// ����
Render_Direct2d::Render_Direct2d() {
	this->WicFactory = nullptr;			// WIC����
	this->factory = nullptr;			// ��Ⱦ����
	this->render_target = nullptr;		// ��Ⱦ��ˢ
	this->textfactory = nullptr;		// ���ֹ���

	// ����
	background_color = D2D1::ColorF(0, 0, 0);
}

// ����
Render_Direct2d::~Render_Direct2d() {

}

// ������Ⱦ��
bool Render_Direct2d::BuildRender(HWND hWnd, int width, int height) {
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
void Render_Direct2d::Release() {

}

// ��ʼ��Ⱦ
void Render_Direct2d::BeginPlay() {
	if (render_target) {
		render_target->BeginDraw();
		render_target->Clear(background_color);

	}
}

// ������Ⱦ
void Render_Direct2d::EndPlay() {
	if (render_target) {
		render_target->EndDraw();
	}
}

// ����ͼ��
ID2D1Bitmap* Render_Direct2d::CreateImage(const char* filename) {
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

// ��ȡͼ���ʽ��������
HRESULT Render_Direct2d::GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename) {
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
