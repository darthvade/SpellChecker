#ifndef __CACHEMANAGER_H__
#define __CACHEMANAGER_H__

#include <string>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

class CheckerCache;

class CacheManager {
	friend class CheckerCache;
	typedef std::vector<CheckerCache*>::iterator Iter;
public:
	CacheManager(const std::string &cachefile, std::string &synccyle); //第二个参数为刷新磁盘周期
	~CacheManager();
	void syncFromRamCache(const std::string &cachefile); //从RAM缓存同步，时间周期到之后同步到磁盘
private:
	void initFromDisk(const std::string &cachefile); //从磁盘文件初始化
	std::vector<CheckerCache*> _vecpRamCache; //保存指向RAM缓存的指针数组
	//clock_t _presynctime; //上一次刷新磁盘时间
	int _synccycle; //刷新磁盘周期（单位：分钟）
	std::unordered_map<std::string, std::string> _disk_cache_map; //查询结果缓存（DiskCache）
};

#endif
