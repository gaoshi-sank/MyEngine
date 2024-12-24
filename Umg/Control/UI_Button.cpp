#include "UI_Button.h"
#include "../UIFactory.h"

// 构造
UI_Button::UI_Button() {
	_text = nullptr;
	click_state = 0;
	button_style = ButtonStyle_Once;
	button_state = 0;
	button_index = 0;
	window_style = UIStyle_Button;
	UIFactory::AddWindow(this);
}

// 析构
UI_Button::~UI_Button() {
	// 图像
	if (!list_image.empty()) {
		for (auto& _image : list_image) {
			if (_image) {
				delete _image;
				_image = nullptr;
			}
		}
		list_image.clear();
	}

	// 文本
	if (_text) {
		delete _text;
		_text = nullptr;
	}
}

void UI_Button::PreRelease() {
	window_release = true;
};

// 创建
bool UI_Button::Create() {
	if (window_release) {
		return false;
	}
	return true;
}

// 创建单图类按钮（包含四个状态的图像）
// 参数：位置和大小
bool UI_Button::Create(const std::string& filename, int x, int y, int w, int h) {
	if (!Create()) {
		return false;
	}

	if (!filename.empty()) {
		auto _image = new SImage(filename.c_str());
		if (!_image) {
			return false;
		}
		else {
			// 设置裁剪
			int width = 0;
			int height = 0;
			auto ret = _image->GetImageSize(width, height);
			if (ret && width != 0 && height != 0) {
				auto srcw = width / 4;
				_image->SetCrop(0, 0, srcw, height);
			}

			// 添加
			list_image.push_back(_image);
		}

		// 设置按钮风格
		button_style = ButtonStyle_Once;
	}

	SetLocation(x, y);
	SetSize(w, h);
	return true;
}

// 增加四个状态图像
// 普通，区域内，按下，失效
bool UI_Button::Create(const std::string& out, const std::string& in, const std::string& down, const std::string& disable) {
	if (!Create()) {
		return false;
	}

	auto build_func = [&](const std::string& filename) {
		auto _image = new SImage(filename.c_str());
		if (!_image) {
			return false;
		}
		else {
			list_image.push_back(_image);
		}
		return true;
	};

	// 设置按钮风格
	button_style = ButtonStyle_Four;
	auto ret = true;
	ret &= build_func(out);
	ret &= build_func(in);
	ret &= build_func(down);
	ret &= build_func(disable);

	return ret;
}

// 增加静态文本
void UI_Button::AddStaticText(const std::string& text) {
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


// 更新事件
void UI_Button::CheckEvent(unsigned int* param) {
	UI_Base::CheckEvent(param);

	if (window_release || !param) {
		return;
	}

	int param_len = param[0];
	if (param_len >= 2) {
		auto message = param[1];
		if (window_mouse) {
			if (message == WM_LBUTTONDOWN) {
				// 区域内按下
				if (window_inrect) {
					// 未按下
					if (click_state == 0) {
						click_state = 1;

						// 按下事件
						if (callback_down) {
							callback_down(nullptr);
						}
					}
				}
				// 区域外按下
				else {
					// 未按下状态
					click_state = 0;
				}
			}
			else if (message == WM_LBUTTONUP) {
				// 区域内放开
				if (window_inrect) {
					// 之前按下过
					if (click_state == 1) {
						// 出发点击事件
						if (callback_click) {
							callback_click(nullptr);
						}
					}

					// 出发放开事件
					if (callback_up) {
						callback_up(nullptr);
					}
				}

				// 修改状态
				click_state = 0;
			}
			else if (message == WM_MOUSEMOVE) {
				// 在区域内移动
				if (window_inrect) {
					// 触发悬停事件
					if (callback_hover) {
						callback_hover(nullptr);
					}
				}
			}
		}
		else if (window_key) {

		}
	}
}

// 更新
void UI_Button::Update() {
	if (window_release) {
		return;
	}

	// 更新状态
	if (window_inrect) {
		if (click_state == 1) {
			button_state = 3;
		}
		else {
			button_state = 2;
		}
	}
	else {
		button_state = 1;
	}

	// 状态更新
	if (!list_image.empty()) {
		if (button_style == ButtonStyle_Once) {
			auto& _image = list_image[0];

			// 设置裁剪
			int width = 0;
			int height = 0;
			auto ret = _image->GetImageSize(width, height);
			if (ret && width != 0 && height != 0) {
				auto srcw = width / 4;
				auto srcx = (button_state - 1) * srcw;
				_image->SetCrop(srcx, 0, srcw, height);
			}

			// 更新
			_image->Update();
		}
		else if (button_style == ButtonStyle_Four) {
			button_index = button_state - 1;
			if (button_index >= 0 && button_index < list_image.size()) {
				list_image[button_index]->Update();
			}
		}
	}
	

	// 文本
	if (_text) {
		_text->Update();
	}

}

// 绘制
void UI_Button::Draw() {
	if (window_release) {
		return;
	}

	// 绘制图像
	if (!list_image.empty()) {
		if (button_style == ButtonStyle_Once) {
			list_image[0]->Draw();
		}
		else if (button_style == ButtonStyle_Four) {
			if (button_index >= 0 && button_index < list_image.size()) {
				list_image[button_index]->Draw();
			}
		}
	}

	// 文本
	if (_text) {
		_text->Draw();
	}

}

// 设置位置
void UI_Button::SetLocation(int x, int y) {
	if (window_release) {
		return;
	}

	this->window_x = x;
	this->window_y = y;

	// 图像
	if (!list_image.empty()) {
		for (auto& _image : list_image) {
			if (_image) {
				_image->SetLocaiton(x, y);
			}
		}
	}

	// 文本
	if (_text) {
		_text->SetLocaiton(x, y);
	}
}

// 设置大小
void UI_Button::SetSize(int w, int h) {
	if (window_release) {
		return;
	}

	this->window_width = w;
	this->window_height = h;

	// 图像
	if (!list_image.empty()) {
		for (auto& _image : list_image) {
			if (_image) {
				_image->SetSize(w, h);
			}
		}
	}

	// 文本
	if (_text) {
		_text->SetSize(w, h);
	}
}

// 设置可见性
void UI_Button::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}

	this->window_visible = visible;
}


// 设置回调
void UI_Button::Event_Hover(std::function<void(int* _param)> _hover) {
	this->callback_hover = _hover;
}

// 设置回调 - 按下
void UI_Button::Event_Down(std::function<void(int* _param)> _down) {
	this->callback_down = _down;
}

// 设置回调 - 放开
void UI_Button::Event_Up(std::function<void(int* _param)> _up) {
	this->callback_up = _up;
}

// 设置回调 - 点击
void UI_Button::Event_Click(std::function<void(int* _param)> _click) {
	this->callback_click = _click;
}
