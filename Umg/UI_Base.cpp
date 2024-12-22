#include "UI_Base.h"

static unsigned int baseid = 0x00;

// 构造
UI_Base::UI_Base() {
	// 基础属性
	this->window_id = ++baseid;				// 窗口编号 
	this->window_style = 0x00;				// 窗口类型 
	this->window_visible = true;			// 默认 - 可见
	this->window_release = false;			// 默认 - 未释放
	this->window_key = false;				// 默认 - 不触发键盘 
	this->window_mouse = true;				// 默认 - 可触发鼠标 
	this->window_renderlevel = 0x00;		// 默认 - 渲染层 0

	// 事件属性
	mouse_posx = mouse_posy = 0;
	window_inrect = false;
	
	// 窗口属性
	this->window_x = this->window_y = this->window_width = this->window_height = 0;
}

// 析构
UI_Base::~UI_Base() {

}