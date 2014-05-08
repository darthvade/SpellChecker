#include "../include/Workthread.h"
#include <string>
#include "../include/Threadpool.h"

#include <iostream> //测试用
#include <cstdlib>

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
	//event
	//compute start
	std::wstring target = Convert::StringToWstring(solve);	
	std::wstring result = _pThreadpool->_checker.findTopKSimilarWords(target, atoi(_pThreadpool->_cfig[4].c_str()));
	solve.clear();
	solve = Convert::WstringToString(result);	
	/*以下测试用*/
	//std::cout << pthread_self() << std::endl;	
	//std::cout << solve << std::endl;	
	//solve += std::string("added-by-server");

	//compute end
}

