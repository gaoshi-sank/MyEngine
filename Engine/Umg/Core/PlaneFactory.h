#ifndef _PlaneFactory_h_
#define _PlaneFactory_h_

#include "UI_Plane.h"

// ���ýṹ
class PlaneSetting {
public:
	// ��������
	int uiId;				// UI�ɱ�ʶID
	int uiType;				// UI����
	int x;					// ����X��
	int y;					// ����Y��
	int width;				// ���ƿ��
	int height;				// ���Ƹ߶�
	int res;				// ��Դ��־λ
	std::string resPath;	// ��Դ·��
	int optionPlane;		// ����Plane���ߵ�������

	// ��������
	std::string lable_title;	// lable��ǩ��

	std::string button_title;	// ��ť��
	int resPath_buttonType;		// ��ť��Դ���
	std::string resPath_out, resPath_in, resPath_down, resPath_disable;

	int resPath_checkBoxType;	// ��ѡ����


	// ����
	PlaneSetting();

	// ����
	~PlaneSetting();
};




// UI������
// ��ȡUI�����ļ������������߶�ӦUI�б�
class PlaneFactory {
public:
	// �����ļ�����һ��UI_Plane
	static UI_Plane* BuildOnePlane(const char* filename);


};




#endif // !_PlaneFactory_h_
