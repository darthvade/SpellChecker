#include "../include/Workthread.h"
#include <string>
#include "../include/Threadpool.h"

Workthread::Workthread() {

}

Workthread::~Workthread() {

}

void Workthread::run() {
	while(true) {
		Task task;
		bool ret = _pThreadpool->get_task_undoneq(task);
		if(ret == false) {
			return;
		}
		compute_task(task.solve);
		ret = _pThreadpool->add_task_doneq(task);
		if(ret == false) {
			return;
		}
	}
}

void Workthread::register_threadpool(Threadpool *pThreadpool) {
	_pThreadpool = pThreadpool;
}

void Workthread::compute_task(std::string &solve) {
	//compute start
	



	//compute end
}

