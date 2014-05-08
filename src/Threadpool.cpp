#include "../include/Threadpool.h"

Threadpool::Threadpool(Config &cfig) : 
_cfig(cfig),
_task_doneq(),
_task_undoneq(),
_max_thread(atoi(_cfig[2].c_str())),
_thread_vector(atoi(_cfig[2].c_str())),
_checker(_cfig[3]),
_is_start(false),
_done_lock(),
_undone_lock(),
_done_cond(&_done_lock),
_undone_cond(&_undone_lock) {
	for(std::vector<Workthread>::iterator iter = _thread_vector.begin(); 
		iter != _thread_vector.end(); ++iter) {
		iter->register_threadpool(this);	
	}
}

Threadpool::~Threadpool() {
	stop_threadpool();
}

void Threadpool::start_threadpool() {
	if(_is_start == false) {
		_is_start = true;
		for(std::vector<Workthread>::iterator iter = _thread_vector.begin();
			iter != _thread_vector.end(); ++iter) {
			iter->start();
		}
	}
}

void Threadpool::stop_threadpool() {
	if(_is_start == false) {
		return;
	}
	_is_start = false;
	_undone_cond.notifyall();
	_done_cond.notifyall();
	for(std::vector<Workthread>::iterator iter = _thread_vector.begin();
		iter != _thread_vector.end(); ++iter) {
		iter->join();
	}
	while(!_task_doneq.empty() || !_task_undoneq.empty()) {
		_task_doneq.pop();
		_task_undoneq.pop();
	}
}

bool Threadpool::add_task_undoneq(Task task) {
	_undone_lock.lock();
	bool ret = false;
	if(_is_start) {
		_task_undoneq.push(task);
		_undone_cond.notify();
		ret = true;
	}
	_undone_lock.unlock();
	return ret;
}

bool Threadpool::get_task_undoneq(Task &task) {
	_undone_lock.lock();
	while(_is_start && _task_undoneq.empty()) {
		_undone_cond.wait();
	}
	if(_is_start == false) {
		_undone_lock.unlock();
		return false;
	}
	task = _task_undoneq.front();
	_task_undoneq.pop();
	_undone_lock.unlock();
	return true;
}

bool Threadpool::add_task_doneq(Task task) {
	_done_lock.lock();
	bool ret = false;
	if(_is_start) {
		_task_doneq.push(task);
		_done_cond.notify();
		ret = true;
	}	
	_done_lock.unlock();
	return ret;
}

bool Threadpool::get_task_doneq(Task &task) {
	_done_lock.lock();
	while(_is_start && _task_doneq.empty())	{
		_done_cond.wait();
	}
	if(_is_start == false) {
		_done_lock.unlock();
		return false;
	}
	task = _task_doneq.front();
	_task_doneq.pop();
	_done_lock.unlock();
	return true;
}

bool Threadpool::add_task(Task task) {
	return add_task_undoneq(task);
}

bool Threadpool::get_task(Task &task) {
	return get_task_doneq(task);
}
