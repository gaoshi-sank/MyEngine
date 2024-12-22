#ifndef _UI_Lable_h_
#define _UI_Lable_h_

#include "../UI_Base.h"

// 标签UI
class UI_Lable : private UI_Base {
private:
	SImage* _image;	// 图像
	SText* _text;	// 文本


public:
	// 构造
	UI_Lable();

	// 析构
	~UI_Lable();

	// 预释放
	virtual void PreRelease();

	// 事件驱动
	virtual void CheckEvent(unsigned int* param);

	// 创建
	virtual bool Create();

	// 创建图像 
	// 参数：位置和大小
	virtual bool Create(const std::string& filename, int x, int y, int w, int h);

	// 增加静态文本
	virtual void AddStaticText(const std::string& text);

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


#endif //!_UI_Lable_h_