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
	std::map<unsigned int, Scene_Base*> MapScene;	// ��������
	unsigned int Scene_Index;						// ��������

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

	// ���볡��
	void AddScene(Scene_Base* _scene);

	// �л�����
	void SwitchScene(unsigned int scene_id);

	// ɾ������
	void DeleteScene(unsigned int scene_id);

private:
	// ����
	void Update();

	// ��Ⱦ
	void Draw();

};

#endif // !_SceneManager_h_
