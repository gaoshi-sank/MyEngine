#include "Scene_Base.h"


static unsigned int id = 0x00;

// ����
Scene_Base::Scene_Base() {
	// ���
	scene_id = ++id;
}

// ����
Scene_Base::~Scene_Base() {

}