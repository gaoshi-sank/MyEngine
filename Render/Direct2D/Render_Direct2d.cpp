#include "Render_Direct2d.h"

static bool isInitCom = false;

// 多字节转为宽字符 
bool CharToWChar(const char* szStr, WCHAR* wszClassName) {
	int result = 0;
	if (wszClassName != nullptr) {
		int wlen = 0, len = (int)strlen(szStr);

		// 转换 
		wlen = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, 0);
		result = MultiByteToWideChar(CP_ACP, 0, szStr, len, wszClassName, wlen);
		if (result != 0) {
			wszClassName[len] = '\0';
		}
	}

	return result;
}

// 构造
Render_Direct2d::Render_Direct2d() {
	this->WicFactory = nullptr;			// WIC工厂
	this->factory = nullptr;			// 渲染工厂
	this->render_target = nullptr;		// 渲染画刷
	this->textfactory = nullptr;		// 文字工厂

	// 属性
	background_color = D2D1::ColorF(0, 0, 0);
}

// 析构
Render_Direct2d::~Render_Direct2d() {

}

// 构建渲染器
bool Render_Direct2d::BuildRender(HWND hWnd, int width, int height) {
	// 结果
	HRESULT hr = S_OK;

	// COM组件初始化
	if (!isInitCom) {
		hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
		hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, __uuidof(this->WicFactory), (LPVOID*)&(this->WicFactory));
		if (FAILED(hr)) {
			return false;
		}
		isInitCom = true;
	}

	// 创建 渲染工厂
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &(factory));
	if (FAILED(hr)) {
		return false;
	}

	// 创建 渲染画刷
	D2D1_SIZE_U Size = D2D1::SizeU(width, height);
	hr = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, Size), &(render_target));
	if (FAILED(hr)) {
		return false;
	}

	// 创建 文字工厂
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(textfactory), reinterpret_cast<IUnknown**>(&textfactory));
	if (FAILED(hr)) {
		return false;
	}

	// 默认返回
	return true;
}

// 释放
void Render_Direct2d::Release() {

}

// 开始渲染
void Render_Direct2d::BeginPlay() {
	if (render_target) {
		render_target->BeginDraw();
		render_target->Clear(background_color);

	}
}

// 结束渲染
void Render_Direct2d::EndPlay() {
	if (render_target) {
		render_target->EndDraw();
	}
}

// 创建图像
ID2D1Bitmap* Render_Direct2d::CreateImage(const char* filename) {
	// 变量列表
	IWICFormatConverter* pConverter = nullptr;
	ID2D1Bitmap* pBitmap = nullptr;
	HRESULT hr = S_OK;
	wchar_t wfilename[260] = { 0 };
	bool result = 0;

	// 转换字符
	result = CharToWChar(filename, wfilename);
	if (result && this->render_target) {
		// 获取格式解析器
		hr = GetFormatConvert(pConverter, wfilename);

		// 由渲染器创建一个图像
		if (SUCCEEDED(hr)) {
			hr = this->render_target->CreateBitmapFromWicBitmap(pConverter, nullptr, &pBitmap);
			if (FAILED(hr)) {
				pBitmap->Release();
				pBitmap = nullptr;
			}
		}

		// 释放临时变量
		if (pConverter) {
			pConverter->Release();
			pConverter = nullptr;
		}
		return pBitmap;
	}
	return nullptr;
}

// 获取图像格式解析对象
HRESULT Render_Direct2d::GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename) {
	// 变量列表
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	ID2D1Bitmap* pBitmap = nullptr;
	HRESULT hr = S_OK;
	int error = 0;								// 错误值

	// 没有错误 - 渲染对象
	if (error || !render_target || !WicFactory) {
		return -1;
	}

	// 创建图像工厂
	// 创建解码器
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

	// 获取帧数量
	UINT counter;
	if ((hr = pDecoder->GetFrameCount(&counter)) != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 获取指定帧的图像
	hr = pDecoder->GetFrame(0, &pFrame);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 创建格式
	hr = WicFactory->CreateFormatConverter(&pConverter);
	if (hr != S_OK) {
		error = GetLastError();
		goto buildip3;
	}

	// 初始化格式
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

	// 释放资源
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
