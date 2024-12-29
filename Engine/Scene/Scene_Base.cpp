#include "Scene_Base.h"


static unsigned int id = 0x00;

// ¹¹Ôì
Scene_Base::Scene_Base() {
	// ±àºÅ
	scene_id = ++id;
}

// Îö¹¹
Scene_Base::~Scene_Base() {

}