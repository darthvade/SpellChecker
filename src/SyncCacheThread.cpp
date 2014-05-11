#include "../include/SyncCacheThread.h"
#include "../include/Threadpool.h"

SyncCacheThread::SyncCacheThread() {

}

SyncCacheThread::~SyncCacheThread() {

}

void SyncCacheThread::run() {
	while(true) {
		_pThreadpool->_cacheMag.syncFromRamCache(_pThreadpool->_cfig[5]);
	}
}

void SyncCacheThread::register_threadpool(Threadpool *pThreadpool) {
	_pThreadpool = pThreadpool;
}


