/**
 * 条件变量类
 *
 *
 */

#ifndef __CONDITION_H__
#define __CONDITION_H__

#include <pthread.h>
#include "Noncopyable.h"
#include "MutexLock.h"

class Condition : public Noncopyable {
public:
	Condition(Mutexlock *);
	~Condition();
	void wait();
	void notify();
	void notifyall();
private:
	Mutexlock *_pMutex;
	pthread_cond_t _cond;
};


#endif
