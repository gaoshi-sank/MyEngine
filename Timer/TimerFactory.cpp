#include "TimerFactory.h"

std::thread* TimerFactory::mainThread = nullptr;
int TimerFactory::thread_status = 0;
std::vector<Timer*> TimerFactory::ListTimer;
std::mutex TimerFactory::lock_List;

// ��ʼ��ʱ�乤��
void TimerFactory::InitTimerFactory() {
	// �����߳�
	if (!mainThread) {
		thread_status = 1;
		mainThread = new std::thread(ThreadLoop);
	}
}

// ֹͣ��ʱ������
void TimerFactory::Release() {
	if (mainThread) {
		thread_status = 0;
		mainThread->join();
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
		ListTimer.push_back(_timer);
	}
	return _timer;
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
			std::vector<Timer*>::iterator it;
			for (it = ListTimer.begin(); it != ListTimer.end();) {
				bool iskeep = true;
				if (*it && (*it)->isrelease()) {
					auto del_node = (*it);
					delete del_node;
					del_node = nullptr;
					iskeep = false;
					it = ListTimer.erase(it);
				}
				if (iskeep) {
					it++;
				}
			}

			// ����
			for (auto& node : ListTimer) {
				if (node) {
					node->update(mainTimer);
				}
			}
		}
	}

}