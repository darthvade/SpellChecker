#include "Config.h"

Config::Config(const char *filename) : _filename(filename), _numfig(0){
	_readConfigFile(_filename);
}

Config::~Config() {

}

void Config::_readConfigFile(std::string &filename) {
	std::fstream fs(filename.c_str());	
	std::string temp;
	while(fs >> temp) {
		if(temp[0] != '#') { 
			_config_vec.push_back(temp);		
		}
	}
	fs.close();
	_numfig = _config_vec.size();
}

std::string& Config::operator[] (const std::size_t index) {
	return index < _numfig ? _config_vec[index] : _error;
}
