#ifndef _Scene_Obejct_h_
#define _Scene_Obejct_h_

#include "Scene_Base.h"


class Scene_Obejct : public  Scene_Base {
public:
	// ����
	Scene_Obejct();

	// ����
	virtual ~Scene_Obejct();

	// ��ʼ��
	virtual void Init();

	// �ͷ�
	virtual void Release();

	// ����
	virtual void Update();

	// ��Ⱦ
	virtual void Draw();

	// ֹͣ
	virtual void Stop();
};

#endif // !_Scene_Obejct_h_
