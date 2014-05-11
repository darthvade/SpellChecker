#include "CacheManager.h"
#include "CheckerCache.h"

#include <iostream> //测试用

CacheManager::CacheManager(const std::string &cachefile, std::string &synccyle) :
_vecpRamCache(),
_synccycle(atoi(synccyle.c_str())),
_disk_cache_map() {
	initFromDisk(cachefile);	
}

CacheManager::~CacheManager() {

}

void CacheManager::initFromDisk(const std::string &cachefile) {
	std::ifstream is(cachefile);
	std::string target;
	std::string result;
	if(!is) {
		std::ofstream os(cachefile);
	}
	while(getline(is, target)) {
		getline(is, result);
		_disk_cache_map.insert({target, result});	
	}
}

void CacheManager::syncFromRamCache(const std::string &cachefile) {
	sleep(_synccycle * 60);
	std::wcout << L"DiskCache Syn!" << std::endl;
	//测试
	std::wcout << _vecpRamCache.size() << std::endl;

	Iter iter = _vecpRamCache.begin();
	while(iter != _vecpRamCache.end()) {
		std::unordered_map<std::string, std::string>::iterator inner = (*iter)->_cache_map.begin();
		while(inner != (*iter)->_cache_map.end()) {
			_disk_cache_map.insert(*inner);	
			//测试
			std::wcout << inner->first.size() << std::endl;
			std::wcout << inner->second.size() << std::endl;
			
			++inner;
		}
		++iter;
	}	
	std::fstream os(cachefile, std::ofstream::out | std::ofstream::app);
	std::unordered_map<std::string, std::string>::iterator mapiter = _disk_cache_map.begin();
	while(mapiter != _disk_cache_map.end()) {
		os << mapiter->first << std::endl;
		os << mapiter->second << std::endl;
		//测试
		std::wcout << mapiter->first.size() << std::endl; 
		std::wcout << mapiter->second.size() << std::endl; 

		++mapiter;
	}	
}


