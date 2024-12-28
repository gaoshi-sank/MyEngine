#ifndef _Scene_Base_h_
#define _Scene_Base_h_

#include "../EngineConfig.h"

// 基础场景类
// 抽象类
class Scene_Base {
public:
	unsigned int scene_id;

public:
	// 构造
	Scene_Base();

	// 析构
	virtual ~Scene_Base();

};

#endif // !_Scene_Base_h_
