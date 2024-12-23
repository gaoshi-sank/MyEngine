#ifndef _UI_TriggerFunction_h_
#define _UI_TriggerFunction_h_

#include "../UI_Base.h"

// 用于触发回调函数
class UI_TriggerFunction {
public:
	// 事件回调指针
	std::function<void(int* _param)> callback_hover;	// 悬停回调
	std::function<void(int* _param)> callback_down;		// 按下回调
	std::function<void(int* _param)> callback_up;		// 放开回调
	std::function<void(int* _param)> callback_click;	// 点击回调

public:
	// 构造
	UI_TriggerFunction() = default;

	// 析构
	~UI_TriggerFunction() = default;

	// 设置回调 - 悬停
	virtual void Event_Hover(std::function<void(int* _param)> _hover) = 0;

	// 设置回调 - 按下
	virtual void Event_Down(std::function<void(int* _param)> _down) = 0;

	// 设置回调 - 放开
	virtual void Event_Up(std::function<void(int* _param)> _up) = 0;

	// 设置回调 - 点击
	virtual void Event_Click(std::function<void(int* _param)> _hover) = 0;

};




#endif // !_UI_TriggerFunction_h_

