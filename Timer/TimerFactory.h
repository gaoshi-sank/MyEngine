#ifndef _TimerFactory_h_
#define _TimerFactory_h_

#include "Timer.h"

// ʱ�������
class TimerFactory {
private:
	static std::thread* mainThread;			// ���߳̾��
	static int thread_status;				// ���߳�״̬
	static std::vector<Timer*> LisTimer;	// ��ʱ���б�
	static std::mutex lock_List;			// �б� - ��

public:
	// ��ʼ��ʱ�乤��
	static void InitTimerFactory();

	// ������ʱ��
	// �ص�����������������Ƿ�ѭ��
	static Timer* SetTimer(std::function<void(int*)> callback_handle, float tiggerTimer, bool isLoop);

	// ֹͣ��ʱ��
	// ��ʱ��ָ��
	static void StopTimer(Timer* handle = nullptr);

private:
	// �߳�����
	static void ThreadLoop();


};

#endif //!_TimerFactory_h_