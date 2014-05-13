#include "../include/CheckerCache.h"
#include "../include/CacheManager.h"

/*
CheckerCache::CheckerCache(CacheManager *pDiskCache) :
_cache_map(),
_pDiscCache(pDiskCache) {
	_pDiscCache->_vecpRamCache.push_back(this); //向CacheManager注册自己
	syncFromDiskCache();
}
*/

CheckerCache::CheckerCache() :
_cache_map(),
_pDiscCache(NULL) {
	//_pDiscCache->_vecpRamCache.push_back(this); //向CacheManager注册自己
	//syncFromDiskCache();
}

CheckerCache::~CheckerCache() {

}

void CheckerCache::initToCacheManager(CacheManager *pDiskCache) {
	_pDiscCache = pDiskCache;
	_pDiscCache->_vecpRamCache.push_back(this); //向CacheManager注册自己
	syncFromDiskCache();
}

std::string CheckerCache::find(std::string &target) {
	Iter iter = _cache_map.find(target);
	if(iter == _cache_map.end()) {
		return std::string();	
	} else {
		return iter->second;
	}
}

void CheckerCache::addresult(std::string target, std::string result) {
	_cache_map.insert({target, result});
}

void CheckerCache::syncFromDiskCache() {
	_cache_map.clear();
	Iter iter = _pDiscCache->_disk_cache_map.begin();
	while(iter != _pDiscCache->_disk_cache_map.end()) {
		_cache_map.insert(*iter);	
		++iter;	
	}
}
