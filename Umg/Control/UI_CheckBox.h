#ifndef _UI_CheckBox_h_
#define _UI_CheckBox_h_

#include "UI_Button.h"
#include "UI_Contain.h"

// ��ѡ��UI
class UI_CheckBox : public UI_Contain, private UI_TriggerFunction {
private:
	std::vector<SImage*> list_image;	// ͼ���б�
	SText* _text;						// �ı�

	// �¼�����
	int check_state;					// ��ť���״̬
	int button_style;					// ��ť���
	int button_state;					// ��ť״̬
	int button_index;					// ��ť��������

private:
	// ö��ֵ
	enum CheckBoxStyle {
		CheckBoxStyle_OneOnce = 1,		// ��ѡ��ť ��ͼ
		CheckBoxStyle_OneFour,			// ��ѡ��ť ��ͼ
		CheckBoxStyle_ChangeOption,		// �л����� 
		CheckBoxStyle_Switch,			// ���
	};


public:
	// ����
	UI_CheckBox();
	
	// ����
	~UI_CheckBox();

	// Ԥ�ͷ�
	virtual void PreRelease();

	// ����
	virtual bool Create();

	// ������ͼ�ఴť�������ĸ�״̬��ͼ��
	// ������λ�úʹ�С
	virtual bool Create(const std::string& filename, int x, int y, int w, int h);

	// �����ĸ�״̬ͼ��
	// ��ͨ�������ڣ����£�ʧЧ
	virtual bool Create(const std::string& out, const std::string& in, const std::string& down, const std::string& disable);

	// ���Ӿ�̬�ı�
	virtual void AddStaticText(const std::string& text);

	// �¼�����
	virtual void CheckEvent(unsigned int* param);

	// ����
	virtual void Update();

	// ����
	virtual void Draw();

	// ����λ��
	virtual void SetLocation(int x, int y);

	// ���ô�С
	virtual void SetSize(int w, int h);

	// ���ÿɼ���
	virtual void SetVisiable(bool visible = false);

	// ���õ�ѡ
	virtual void SetCheckBoxType(int _type);

	// ����������
	virtual void SetGroupId(int _id);

	// ���ûص� - ��ͣ
	virtual void Event_Hover(std::function<void(int* _param)> _hover);

	// ���ûص� - ����
	virtual void Event_Down(std::function<void(int* _param)> _down);

	// ���ûص� - �ſ�
	virtual void Event_Up(std::function<void(int* _param)> _up);

	// ���ûص� - ���
	virtual void Event_Click(std::function<void(int* _param)> _hover);
};


#endif // !_UI_CheckBox_h_
