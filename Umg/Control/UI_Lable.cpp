#include "UI_Lable.h"
#include "../UIFactory.h"

// ����
UI_Lable::UI_Lable() {
	_image = nullptr;
	_text = nullptr;
	UIFactory::AddWindow(this);
}

// ����
UI_Lable::~UI_Lable() {
	// ͼ��
	if (_image) {
		delete _image;
		_image = nullptr;
	}

	// �ı�
	if (_text) {
		delete _text;
		_text = nullptr;
	}
}

void UI_Lable::PreRelease(){
	window_release = true;
};

// ����
bool UI_Lable::Create() {
	if (window_release) {
		return false;
	}
	return true;
}

// ����ͼ�� 
// ������λ�úʹ�С
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

// ���Ӿ�̬�ı�
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

// �¼�����
void UI_Lable::CheckEvent(unsigned int* param) {
	if (window_release || !param) {
		return;
	}
	int param_len = param[0];
	if (param_len >= 2) {
		auto message = param[1];

		// �������λ��
		if (window_mouse && message == WM_MOUSEMOVE) {
			// Ĭ�ϲ��ڴ���
			window_inrect = false;

			// ��ȷ��ȡ
			if (param_len >= 3) {
				LPARAM lParam = (LPARAM)param[2];
				mouse_posx = GET_X_LPARAM(lParam);
				mouse_posy = GET_Y_LPARAM(lParam);

				// �ж�������
				if (Point_In_Rect(mouse_posx, mouse_posy, window_x, window_y, window_width, window_height)) {
					window_inrect = true;
				}
			}
		}
	}
}


// ����
void UI_Lable::Update() {
	if (window_release) {
		return;
	}

	// ͼ��
	if (_image) {
		_image->Update();
	}

	// �ı�
	if (_text) {
		_text->Update();
	}

}

// ����
void UI_Lable::Draw() {
	if (window_release) {
		return;
	}

	// ͼ��
	if (_image) {
		_image->Draw();
	}

	// �ı�
	if (_text) {
		_text->Draw();
	}

}

// ����λ��
void UI_Lable::SetLocation(int x, int y) {
	if (window_release) {
		return;
	}

	this->window_x = x;
	this->window_y = y;

	// ͼ��
	if (_image) {
		_image->SetLocaiton(x, y);
	}

	// �ı�
	if (_text) {
		_text->SetLocaiton(x, y);
	}
}

// ���ô�С
void UI_Lable::SetSize(int w, int h) {
	if (window_release) {
		return;
	}

	this->window_width = w;
	this->window_height = h;

	// ͼ��
	if (_image) {
		_image->SetSize(w, h);
	}


	// �ı�
	if (_text) {
		_text->SetSize(w, h);
	}
}

// ���ÿɼ���
void UI_Lable::SetVisiable(bool visible) {
	if (window_release) {
		return;
	}

	this->window_visible = visible;
}
