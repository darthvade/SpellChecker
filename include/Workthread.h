/**
 * 工作线程类
 *
 */

#ifndef __WORKTHREAD_H__
#define __WORKTHREAD_H__

#include "Thread.h"
#include <string>

class Threadpool;

class Workthread : public Thread {
public:
	Workthread();
	~Workthread();
	void run(); //工作逻辑实现
	void register_threadpool(Threadpool *); //注册线程池
	void compute_task(std::string &); //实际处理逻辑
private:
	Threadpool *_pThreadpool;
};

#endif
