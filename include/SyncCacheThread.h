/**
 *	同步Cache线程类
 *
 */

#ifndef __SYNCCACHETHREAD_H__
#define __SYNCCACHETHREAD_H__

#include "Thread.h"

class Threadpool;

class SyncCacheThread : public Thread {
public:
	SyncCacheThread();
	~SyncCacheThread();
	void run(); //实现工作逻辑
	void register_threadpool(Threadpool *); //注册线程池
private:
	Threadpool *_pThreadpool;
};

#endif
