#include "UI_Lable.h"
#include "../UIFactory.h"

// 构造
UI_Lable::UI_Lable() {
	_image = nullptr;
	_text = nullptr;
	UIFactory::AddWindow(this);
}

// 析构
UI_Lable::~UI_Lable() {
	// 图像
	if (_image) {
		delete _image;
		_image = nullptr;
	}

	// 文本
	if (_text) {
		delete _text;
		_text = nullptr;
	}
}

void UI_Lable::PreRelease(){
	window_release = true;
};

// 创建
bool UI_Lable::Create() {
	if (window_release) {
		return false;
	}
	return true;
}

// 创建图像 
// 参数：位置和大小
bool UI_Lable::Create(const std::string& filename, int x, int y, int w, int h) {
	if (!Create()) {
		return false;
	}

	if (!filename.empty() && !_image) {
		_image = new SImage(filename.c_str());
		if (!_image) {
			return false;
		}
	}

	SetLocation(x, y);
	SetSize(w, h);
	return true;
}

// 增加静态文本
void UI_Lable::AddStaticText(const std::string& text) {
	if (window_release) {
		return;
	}

	if (!_text) {
		_text = new SText(text.c_str());
	}
	else {
		_text->ReSetText(text.c_str());
	}

	if (_text) {
		_text->SetLocaiton(window_x, window_y);
		_text->SetSize(window_width, window_height);
		_text->ReSetLayout();
	}
}

// 事件驱动
void UI_Lable::CheckEvent(unsigned int* param) {
	if (window_release || !param) {
		return;
	}
	int param_len = param[0];
	if (param_len >= 2) {
		auto message = param[1];

		// 基础光标位置
		if (window_mouse && message == WM_MOUSEMOVE) {
			// 默认不在窗口
			window_inrect = false;

			// 正确获取
			if (param_len >= 3) {
				LPARAM lParam = (LPARAM)param[2];
				mouse_posx = GET_X_LPARAM(lParam);
				mouse_posy = GET_Y_LPARAM(lParam);

				// 判断区域内
				if (Point_In_Rect(mouse_posx, mouse_posy, window_x, window_y, window_width, window_height)) {
					window_inrect = true;
				}
			}
		}
	}
}


// 更新
void UI_Lable::Update() {
	if (window_release) {
		return;
	}

	// 图像
	if (_image) {
		_image->Update();
	}

	// 文本
	if (_text) {
		_text->Update();
	}

}

// 绘制
void UI_Lable::Draw() {
	if (window_release) {
		return;
	}

	// 图像
	if (_image) {
		_image->Draw();
	}

	// 文本
	if (_text) {
		_text->Draw();
	}

}

// 设置位置
void UI_Lable::SetLocation(int x, int y) {
	if (window_release) {
		return;
	}

	this->window_x = x;
	this->window_y = y;

	// 图像
	if (_image) {
		_image->SetLocaiton(x, y);
	}

	// 文本
	if (_text) {
		_text->SetLocaiton(x, y);
	}
}

// 设置大小
void UI_Lable::SetSize(int w, int h) {
	if (window_release) {
		return;
	}

	this->window_width = w;
	this->window_height = h;

	// 图像
	if (_image) {
		_image->SetSize(w, h);
	}


	// 文本
	if (_text) {
		_text->SetSize(w, h);
	}
}

// 设置可见性
void UI_Lable::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}

	this->window_visible = visible;
}
