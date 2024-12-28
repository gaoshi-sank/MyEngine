#ifndef _SceneManager_h_
#define _SceneManager_h_

#include "Scene_Base.h"

// ��������
class SceneManager {
private:
	// ����
	SceneManager();

	// ����
	~SceneManager();

	// ��ֵ̬
	static SceneManager* g_sceneManger;

	// ����
	std::vector<Scene_Base*> ListScene;
	std::mutex lock_List;

public:
	// ��ʼ������
	static void InitSceneManager();

	// �ͷ�
	static void Release();

	// ��ȡ����
	static SceneManager* GetInstance();

	// ����
	static void UpdateScene();

	// ����
	static void DrawScene();


private:


};

#endif // !_SceneManager_h_
