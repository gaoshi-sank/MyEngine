#ifndef _SceneManager_h_
#define _SceneManager_h_

#include "Scene_Obejct.h"

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
	std::map<unsigned int, Scene_Obejct*> MapScene;	// ��������
	unsigned int Scene_Index;						// ��������

public:
	// ��ʼ������
	static void InitSceneManager();

	// �ͷ�
	static void ReleaseScene();

	// ��ȡ����
	static SceneManager* GetInstance();

	// ����
	static void UpdateScene();

	// ����
	static void DrawScene();

	// ���볡��
	void AddScene(Scene_Obejct* _scene);

	// �л�����
	void SwitchScene(unsigned int scene_id);

	// ɾ������
	void DeleteScene(unsigned int scene_id);

private:
	// ��ʼ��
	void Init();

	// ����
	void Update();

	// ��Ⱦ
	void Draw();

	// �ͷ�
	void Release();

};

#endif // !_SceneManager_h_
