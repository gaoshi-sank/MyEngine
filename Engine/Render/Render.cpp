#include "Render.h"
#include "RenderFactory.h"

static bool isInitCom = false;

// 构造
Render::Render() {
	this->WicFactory = nullptr;			// WIC工厂
	this->factory = nullptr;			// 渲染工厂
	this->render_target = nullptr;		// 渲染画刷
	this->textfactory = nullptr;		// 文字工厂

	// 属性
	background_color = D2D1::ColorF(0, 0, 0);
}

// 析构
Render::~Render() {

}

// 构建渲染器
bool Render::BuildRender(HWND hWnd, int width, int height) {
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
void Render::Release() {

}

// 开始渲染
void Render::BeginPlay() {
	if (render_target) {
		render_target->BeginDraw();
		render_target->Clear(background_color);

	}
}

// 结束渲染
void Render::EndPlay() {
	if (render_target) {
		render_target->EndDraw();
	}
}

// 绘制图像
void Render::RenderImage(ID2D1Bitmap* image, D2D1_RECT_F rect, D2D1_RECT_F src_rect, float opacity, float angle) {
	if (render_target && image) {
		render_target->DrawBitmap(image, rect, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src_rect);
	}
}

// 绘制文本
void Render::RenderText(wchar_t* render_text, D2D1_RECT_F text_rect, IDWriteTextLayout* layout, ID2D1SolidColorBrush* brash) {
	if (render_target && render_text && layout && brash) {
		render_target->DrawText(render_text, UINT32(wcslen(render_text)), layout, text_rect, brash, D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
}

// 创建图像
ID2D1Bitmap* Render::CreateImage(const char* filename) {
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

// 创建文本布局
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

// 创建文本格式
IDWriteTextFormat* Render::CreateTextFormat(float font_size) {
	IDWriteTextFormat* textformat = nullptr;
	if (textfactory) {
		textfactory->CreateTextFormat(
			L"宋体", 
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

// 创建画刷
ID2D1SolidColorBrush* Render::CreateBrush(D2D1_COLOR_F _color) {
	ID2D1SolidColorBrush* color_brush = nullptr;
	if (render_target) {
		render_target->CreateSolidColorBrush(_color, &color_brush);
	}
	return color_brush;
}

// 设置文本风格
void Render::SetTextStyle(IDWriteTextLayout* _layout, int horizontal, int vertical, int swrapping) {
	if (_layout) {
		// 水平
		switch (horizontal) {
		case 1: 
		{
			// 水平居中 - 默认
			_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			break;
		}
		case 2:
		{
			// 字体铺满区域 - 可能存在拉伸
			_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
			break;
		}
		case 3:	
		{
			// 水平居右
			_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
			break;
		}	
		default:
		{
			// 水平居左
			_layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			break;
		}
		}

		// 垂直
		switch (vertical) {
		case 1: 
		{
			// 下边
			_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);	
			break;
		}
		case 2: 
		{
			// 上边
			_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			break;
		}
		default: {
			// 垂直居中 - 默认
			_layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);	
			break;
		}
		}

		// 换行
		switch (vertical) {
		case 1: 
		{
			// 文字跨行打断，以避免文字溢出布局框
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
			// 保持在同一行
			_layout->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
			break;
		}
		}
	}
}

// 获取图像格式解析对象
HRESULT Render::GetFormatConvert(IWICFormatConverter*& pConverter, LPCWSTR filename) {
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
