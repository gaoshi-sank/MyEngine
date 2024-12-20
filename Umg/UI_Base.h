#ifndef _UI_Base_h_
#define _UI_Base_h_

// 包含文件
#include "../Render/Sprite/SSprite.h"	// 渲染用精灵

// 控件
class UI_Base {
public:
	// 基础属性
	unsigned int window_id;		// 窗口编号 
	unsigned int window_style;	// 窗口类型 
	bool window_visible;		// 可见性
	bool window_release;		// 释放性
	bool window_key;			// 可触发键盘事件 
	bool window_mouse;			// 可触发鼠标事件
	int window_renderlevel;		// 窗口渲染层
	int window_x;				// 窗口区域 X
	int window_y;
	int window_width;			
	int window_height;			// 窗口区域 height

public:
	// 构造
	UI_Base();

	// 析构
	virtual ~UI_Base();

	// 事件驱动
	virtual void CheckEvent(int* param) = 0;

	// 更新
	virtual void Update() = 0;

	// 绘制
	virtual void Draw() = 0;

	// 设置位置
	virtual void SetLocation(int x, int y) = 0;

	// 设置大小
	virtual void SetSize(int x, int y) = 0;

	// 设置可见性
	virtual void SetVisiable(bool life) = 0;
};


#endif //!_UI_Base_h_