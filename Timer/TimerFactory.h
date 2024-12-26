#ifndef _TimerFactory_h_
#define _TimerFactory_h_

#include "Timer.h"

// ʱ�������
class TimerFactory {
private:


public:
	// ��ʼ��ʱ�乤��
	static void InitTimerFactory();

	// ������ʱ��
	// �ص�����������������Ƿ�ѭ��
	static Timer* SetTimer(std::function<void(int*)> callback_handle, float tiggerTimer, bool isLoop);

	// ֹͣ��ʱ��
	// ��ʱ��ָ��
	static void StopTimer(Timer* handle = nullptr);

};

#endif //!_TimerFactory_h_