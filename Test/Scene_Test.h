#ifndef _Scene_Test_h_
#define _Scene_Test_h_


#include "../Engine/EngineProvider.h"

// 测试场景
class Scene_Test : public Scene_Base {
private:
	UI_Plane* _test;
	bool isinit = false;
	int isclick = 0;

	std::vector<UI_Base*> listTest;
	std::shared_ptr<SImage> sfmlTest;

public:
	// 构造
	Scene_Test();

	// 析构
	virtual ~Scene_Test();

	// 初始化
	virtual void Init() override;

	// 释放
	virtual void Release() override;

	// 更新
	virtual void Update() override;

	// 渲染
	virtual void Draw() override;

	// 停止
	virtual void Stop() override;

	// 面板UI事件处理
	virtual void EventControl(int uiType, int ui_id, int msgType, int message);

};

#endif // !_Scene_Test_h_