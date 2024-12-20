#ifndef _UI_Lable_h_
#define _UI_Lable_h_

#include "../UI_Base.h"

// 标签UI
class UI_Lable : private UI_Base {
private:

public:
	// 构造
	UI_Lable();

	// 析构
	~UI_Lable();

	// 事件驱动
	virtual void CheckEvent(int* param);

	// 更新
	virtual void Update();

	// 绘制
	virtual void Draw();

	// 设置位置
	virtual void SetLocation(int x, int y);

	// 设置大小
	virtual void SetSize(int x, int y);

	// 设置可见性
	virtual void SetVisiable(bool life);
};


#endif //!_UI_Lable_h_