#ifndef _SceneManager_h_
#define _SceneManager_h_

#include "Scene_Base.h"

// 场景管理
class SceneManager {
private:
	// 构造
	SceneManager();

	// 析构
	~SceneManager();

	// 静态值
	static SceneManager* g_sceneManger;

	// 属性
	std::vector<Scene_Base*> ListScene;
	std::mutex lock_List;

public:
	// 初始化引擎
	static void InitSceneManager();

	// 释放
	static void Release();

	// 获取引擎
	static SceneManager* GetInstance();

	// 更新
	static void UpdateScene();

	// 绘制
	static void DrawScene();


private:


};

#endif // !_SceneManager_h_
