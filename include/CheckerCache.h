/**
 *
 * 内存Cache类
 * 作用：用于保存用户已查询的单词的返回结果，以提高下一次查询相同单词的查询速度
 * 注：Cache物理结构为hashtable
 *
 */

#ifndef __CHECKERCACHE_H__
#define __CHECKERCACHE_H__

#include <string>
#include <unordered_map>

class CacheManager;

class CheckerCache {
	friend class Threadpool;
	friend class CacheManager;
	typedef std::unordered_map<std::string, std::string>::iterator Iter;
public:
	//CheckerCache(CacheManager *pDiskCache);
	CheckerCache();
	~CheckerCache();	
	std::string find(std::string &); //在Cache中查询结果
	void addresult(std::string, std::string); //向Cache中添加新的查询结果
	void initToCacheManager(CacheManager *pDiskCache); 
private:
	void syncFromDiskCache(); //与磁盘Cache同步
	std::unordered_map<std::string, std::string> _cache_map; //查询结果缓存（Cache）
	CacheManager *_pDiscCache; //指向磁盘Cache的指针
};

#endif
