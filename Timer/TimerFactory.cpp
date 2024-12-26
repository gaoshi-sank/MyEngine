#include "TimerFactory.h"

std::thread* TimerFactory::mainThread = nullptr;
int TimerFactory::thread_status = 0;
std::mutex TimerFactory::lock_List;

// ��ʼ��ʱ�乤��
void TimerFactory::InitTimerFactory() {


	// �����߳�
	if (!mainThread) {
		thread_status = 1;
		mainThread = new std::thread(ThreadLoop);
		mainThread->detach();
	}
}

// ������ʱ��
// �ص�����������������Ƿ�ѭ��
Timer* TimerFactory::SetTimer(std::function<void(int* param)> callback_handle, float tiggerTimer, bool isLoop) {
	Timer* _timer = new Timer(callback_handle);
	if (_timer) {
		_timer->setLine(tiggerTimer);
		_timer->setLoop(isLoop);
		_timer->start();

		std::lock_guard<std::mutex> lock(lock_List);
		LisTimer.push_back(_timer);
	}
	return _timer;
}

// ֹͣ��ʱ��
// ��ʱ��ָ��
void TimerFactory::StopTimer(Timer* handle) {

}

// �߳�����
void TimerFactory::ThreadLoop() {

	LARGE_INTEGER mainTimer;
	
	while (thread_status) {
		QueryPerformanceCounter(&mainTimer);

		{
			// ������ʼ
			std::lock_guard<std::mutex> lock(lock_List);

			// ɾ��


			// ����
			for (auto& node : LisTimer) {
				if (node) {
					node->update(mainTimer);
				}
			}
		}
	}
	thread_status = 2;

}