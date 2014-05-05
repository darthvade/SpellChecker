#include "MutexLock.h"

Mutexlock::Mutexlock() {
	pthread_mutex_init(&_mutex, NULL);
}

Mutexlock::~Mutexlock() {
	pthread_mutex_destroy(&_mutex);
}

void Mutexlock::lock() {
	pthread_mutex_lock(&_mutex);
}

void Mutexlock::unlock() {
	pthread_mutex_unlock(&_mutex);
}
