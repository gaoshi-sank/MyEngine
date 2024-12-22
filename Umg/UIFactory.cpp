#include "UIFactory.h"

static UIFactory* g_ui = nullptr;

// ����
UIFactory::UIFactory() {

}

// ����
UIFactory::~UIFactory() {

}


// ��ʼ��
void UIFactory::InitUIProvider() {
	if (!g_ui) {
		g_ui = new UIFactory();
	}
}

// �ͷ�
void UIFactory::Release() {

}

// ��ӿؼ�
void UIFactory::AddWindow(UI_Base* _ui) {
	if (g_ui) {
		std::lock_guard<std::mutex> lck(g_ui->lockAddlist);
		bool isdiff = true;
		for (auto& node : g_ui->addList) {
			if (node && _ui && (node == _ui || node->window_id == _ui->window_id)) {
				isdiff = false;
				break;
			}
		}
		if (isdiff) {
			g_ui->addList.push_back(_ui);
		}
	}
}

// ɾ���ؼ�
void UIFactory::DelWindow(UI_Base* _ui) {
	if (g_ui) {
		std::lock_guard<std::mutex> lck(g_ui->lockDellist);
		bool issame = false;
		for (auto& node : g_ui->delList) {
			if (node && _ui && (node == _ui || node->window_id == _ui->window_id)) {
				issame = true;
				break;
			}
		}
		if (issame) {
			g_ui->delList.push_back(_ui);
		}
	}
}


// �¼�����
void UIFactory::CheckEvent(unsigned int* param) {
	if (g_ui && param) {
		for (auto& _ui : g_ui->list) {
			if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
				_ui->CheckEvent(param);
			}
		}
	}
}

// ����
void UIFactory::Update() {
	if (g_ui) {
		std::lock_guard<std::mutex> lck(g_ui->lockList);

		// ɾ��
		for (auto& delui : g_ui->delList) {
			if (delui) {
				bool isdel = false;
				for (auto i = 0; i < g_ui->list.size(); i++) {
					auto& node = g_ui->list[i];
					if (node && (node == delui || node->window_id == delui->window_id)) {
						delete node;
						node = nullptr;
						g_ui->list.erase(g_ui->list.begin() + i);
						isdel = true;
						break;
					}
				}
			}
		}
		g_ui->delList.clear();

		// �����ЧUI
		std::vector<UI_Base*>::iterator it;
		for (it = g_ui->list.begin(); it != g_ui->list.end(); ) {
			auto& node = (*it);
			bool iskeep = true;
			if (node && (node->window_id == 0x00 || node->window_release)) {
				delete node;
				node = nullptr;
				it = g_ui->list.erase(it);
				iskeep = false;
			}
			if (iskeep) {
				it++;
			}
		}

		// ����
		for (auto& addui : g_ui->addList) {
			if (addui) {
				bool isdiff = true;
				for (auto i = 0; i < g_ui->list.size(); i++) {
					auto& node = g_ui->list[i];
					if (node && (node == addui || node->window_id == addui->window_id)) {
						isdiff = false;
						break;
					}
				}
				if (isdiff) {
					g_ui->list.push_back(addui);
				}
			}
		}
		g_ui->addList.clear();

		// ����
		for (auto& _ui : g_ui->list) {
			if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
				_ui->Update();
			}
		}
	}
}

// ��Ⱦ
void UIFactory::Draw() {
	if (g_ui) {
		std::lock_guard<std::mutex> lck(g_ui->lockList);
		for (auto& _ui : g_ui->list) {
			if (_ui && _ui->window_id != 0x00 && !_ui->window_release) {
				_ui->Draw();
			}
		}
	}
}

// �ж϶���
bool UIFactory::GetLevelTop(int pos_x, int pos_y, UI_Base* other) {
	if (g_ui) {
		// ��ȡ�ɼ�-����UI�ؼ�
		std::vector<UI_Base*> alltop;


		// ����
		if (!alltop.empty()) {
			
		}
	}
	return false;
}
