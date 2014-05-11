/**
 *	线程池类
 *
 */

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <queue>
#include <vector>
#include "MutexLock.h"
#include "Condition.h"
#include "Noncopyable.h"
#include "Workthread.h"
#include "Config.h"
#include <cstdlib>
#include <string>
#include "WstringConvertString.hpp"
#include "Checker.h"
#include "CacheManager.h"
#include "SyncCacheThread.h"
#include "CheckerCache.h"

struct Task {
	unsigned int ip; //任务提交方ip
	unsigned int port; //任务提交方port
	std::string solve; //提交的任务 或 待返回结果
};

class Threadpool : public Noncopyable {
friend class Workthread;
friend class SyncCacheThread;
public:
	Threadpool(Config &);
	~Threadpool();
	void start_threadpool(); //启动线程池
	void stop_threadpool(); //关闭线程池
	bool add_task(Task task); //向线程池中放入任务（实际放入任务等待队列）
	bool get_task(Task &task); //从线程池中取出已处理完成的任务（实际从任务返程队列取得）
private:
	bool add_task_undoneq(Task task); //向任务等待队列中添加任务
	bool get_task_undoneq(Task &task); //从任务等待队列中取得任务
	bool add_task_doneq(Task task); //向任务完成队列中添加任务
	bool get_task_doneq(Task &task); //从任务完成队列中取得任务

	Config _cfig; //程序配置信息
	std::queue<Task> _task_doneq; //任务等待队列
	std::queue<Task> _task_undoneq; //任务完成队列
	std::vector<Workthread>::size_type _max_thread; //最大线程数
	std::vector<Workthread> _thread_vector; //线程队列
	CacheManager _cacheMag;	//磁盘Cache
	std::vector<CheckerCache> _cacheVec; //内存Cache数组
	SyncCacheThread _syncThread; //磁盘Cache同步线程
	
	Checker _checker; //字符匹配对象

	bool _is_start; //线程池是否启动
	mutable Mutexlock _done_lock; //任务等待队列锁
	mutable Mutexlock _undone_lock; //任务完成队列锁
	mutable Condition _done_cond; //任务等待队列条件变量
	mutable Condition _undone_cond; //任务完成队列条件变量
};

#endif
