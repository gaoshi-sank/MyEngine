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

	// 初始化
	virtual void Init() = 0;

	// 释放
	virtual void Release() = 0;

	// 更新
	virtual void Update() = 0;

	// 渲染
	virtual void Draw() = 0;

	// 停止
	virtual void Stop() = 0;
};

#endif // !_Scene_Base_h_
