/**
 *	Config类
 *  作用：用于管理配置文件的每一个选项。
 *  使用：使用下标访问每个配置数据。
 *  备注：配置文件的每一行为一个选项，注释以'#'号开头
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <vector>
#include <string>
#include <fstream>

class Config {
public:
	Config(const char *);
	~Config();
	std::string& operator[] (const std::size_t); //通过下表访问配置选项
private:	
	void _readConfigFile(std::string &); //读取配置文件到维护数组
	std::string _filename; //配置文件名
	std::size_t _numfig; //配置属性数量
	std::vector<std::string> _config_vec; //配置选项维护数组
	std::string _error; //下标访问越界时返回的空字符串
};

#endif
