#ifndef _UI_Plane_h_
#define _UI_Plane_h_


#include "../Control/UI_Lable.h"		// 标签UI
#include "../Control/UI_Button.h"		// 按钮UI
#include "../Control/UI_CheckBox.h"		// 按钮UI


// 面板类
// 一般用于放置其他UI控件
class UI_Plane : public UI_Base {
private:
	std::vector<UI_Base*> ListAttached;	// 附属UI列表
	std::mutex lockList;

public:
	// 构造
	UI_Plane();

	// 析构
	virtual ~UI_Plane();

	// 预释放
	virtual void PreRelease();

	// 创建
	virtual bool Create();

	// 加入附属UI
	virtual void AddAttachedUI(UI_Base* _ui);

	// 事件驱动
	virtual void CheckEvent(unsigned int* param);

	// 更新
	virtual void Update();

	// 绘制
	virtual void Draw();

	// 设置位置
	virtual void SetLocation(int x, int y);

	// 设置大小
	virtual void SetSize(int w, int h);

	// 设置可见性
	virtual void SetVisiable(bool visible = false);

};


#endif // !_UI_Plane_h_
