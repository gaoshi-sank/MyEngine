#ifndef _TimerFactory_h_
#define _TimerFactory_h_

#include "Timer.h"

// 时间管理类
class TimerFactory {
private:


public:
	// 初始化时间工厂
	static void InitTimerFactory();

	// 创建计时器
	// 回调函数，触发间隔，是否循环
	static Timer* SetTimer(std::function<void(int*)> callback_handle, float tiggerTimer, bool isLoop);

	// 停止计时器
	// 计时器指针
	static void StopTimer(Timer* handle = nullptr);

};

#endif //!_TimerFactory_h_