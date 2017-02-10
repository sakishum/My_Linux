#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

template <typename TYPE, void (TYPE::*RunThread)()>
void *thread_t(void *param) {
    TYPE *thiz = (TYPE *)param;
    thiz->RunThread();
    return NULL;
}

// 线程包装类
class OuterThread {
public:
	OuterThread(double interval);
	virtual ~OuterThread(void);
	// 启动
	int start(void);

protected:
	static void *threadWorkerProxy(void *args);
	void timerWorker(void);

private:
	double m_interval;
};

OuterThread::OuterThread(double interval) : m_interval(interval) {
}

OuterThread::~OuterThread(void) {
}

int OuterThread::start(void) {
	pthread_attr_t attr;
	pthread_attr_init (&attr);
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);	// 不能用 pthread_join() 来同步, 线程结束时自动释放资源

	int ret;
	pthread_t thread;
	//ret = pthread_create(&thread, &attr, thread_t<OuterThread, &OuterThread::threadWorkerProxy>, this);
	ret = pthread_create(&thread, &attr, &OuterThread::threadWorkerProxy, this);
	if (ret != 0){
		printf("Thread creation failed:%d",ret);	
		return ret;
	}

	pthread_attr_destroy(&attr);
	return 0;
}

// 线程函数的起始地址
void *OuterThread::threadWorkerProxy(void *args) {
	OuterThread *thread = reinterpret_cast<OuterThread*>(args);

	thread->timerWorker();

	return NULL;
}

void OuterThread::timerWorker(void) {
	int usInterval = (int)(m_interval * 1000000);
	while (1) {
		// 每一次进入都休眠 usInterval us
		usleep(usInterval);
		// Thread work
		printf("Hello\n");
	}
}

int main(int, char**) {
	int ret = 0;

	OuterThread *outerTimerThread = new OuterThread(2.0f);
	if ((ret = outerTimerThread->start())) {
		printf("innerHandleThread start fail: %d\n", ret);
	}

	while (1) {
		// 每一秒循环一次，其他都是线程
		 sleep(1);
	}

	exit(EXIT_SUCCESS);
}

