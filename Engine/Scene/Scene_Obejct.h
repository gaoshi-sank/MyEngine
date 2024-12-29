#ifndef _Scene_Obejct_h_
#define _Scene_Obejct_h_

#include "Scene_Base.h"


class Scene_Obejct : public  Scene_Base {
public:
	// 构造
	Scene_Obejct();

	// 析构
	virtual ~Scene_Obejct();

	// 初始化
	virtual void Init();

	// 释放
	virtual void Release();

	// 更新
	virtual void Update();

	// 渲染
	virtual void Draw();

	// 停止
	virtual void Stop();
};

#endif // !_Scene_Obejct_h_
