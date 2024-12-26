#include "TimerFactory.h"

// 初始化时间工厂
void TimerFactory::InitTimerFactory() {

}

// 创建计时器
// 回调函数，触发间隔，是否循环
Timer* TimerFactory::SetTimer(std::function<void(int* param)> callback_handle, float tiggerTimer, bool isLoop) {

}

// 停止计时器
// 计时器指针
void TimerFactory::StopTimer(Timer* handle) {

}