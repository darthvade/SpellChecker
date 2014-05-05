/**
 * 线程基类
 * 注：子类实现其run方法来实现自己的业务逻辑
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <cstddef>

class Thread {
public:
	Thread();
	~Thread();
	void start();
	void join();
	static void *thread_func(void *);
	virtual void run() = 0;
	pthread_t get_tid() const;
protected:
	pthread_t _tid;	
};

#endif
