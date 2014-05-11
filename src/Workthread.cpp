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
	srand(clock());
	int selectCache = rand() % atoi(_pThreadpool->_cfig[2].c_str());
	//测试
	std::wcout << selectCache << std::endl;

	std::string cacheresult(_pThreadpool->_cacheVec[selectCache].find(solve));
	if(cacheresult.size() != 0) {
		solve.clear();
		solve = cacheresult;	
	} else {
		std::wstring target = Convert::StringToWstring(solve);	
		std::wstring result = _pThreadpool->_checker.findTopKSimilarWords(target, atoi(_pThreadpool->_cfig[4].c_str()));
		_pThreadpool->_cacheVec[selectCache].addresult(solve, Convert::WstringToString(result));
		solve.clear();
		solve = Convert::WstringToString(result);	
	}
	/*
	std::wstring target = Convert::StringToWstring(solve);	
	std::wstring result = _pThreadpool->_checker.findTopKSimilarWords(target, atoi(_pThreadpool->_cfig[4].c_str()));
	solve.clear();
	solve = Convert::WstringToString(result);	
	*/
	//compute end
}






