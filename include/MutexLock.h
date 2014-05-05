/**
 * 互斥锁类
 *
 */

#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include <pthread.h>
#include "Noncopyable.h"

class Condition;

class Mutexlock : public Noncopyable {
	friend class Condition;
public:
	Mutexlock();
	~Mutexlock();
	void lock();
	void unlock();
private:
	pthread_mutex_t _mutex;
};


#endif
