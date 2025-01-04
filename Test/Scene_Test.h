#ifndef _Scene_Test_h_
#define _Scene_Test_h_


#include "../Engine/EngineProvider.h"

// ���Գ���
class Scene_Test : public Scene_Base {
private:
	UI_Plane* _test;
	bool isinit = false;
	int isclick = 0;

public:
	// ����
	Scene_Test();

	// ����
	virtual ~Scene_Test();

	// ��ʼ��
	virtual void Init() override;

	// �ͷ�
	virtual void Release() override;

	// ����
	virtual void Update() override;

	// ��Ⱦ
	virtual void Draw() override;

	// ֹͣ
	virtual void Stop() override;

	// ���UI�¼�����
	virtual void EventControl(int uiType, int ui_id, int msgType, int message);

};

#endif // !_Scene_Test_h_