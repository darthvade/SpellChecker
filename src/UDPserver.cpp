#include "UDPserver.h"
#include <iostream>
#include <errno.h>


UDPserver::UDPserver(cst &ip, cst &port) {
	_fd_server = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&_server_addr, 0, sizeof(_server_addr));	
	_server_addr.sin_family = AF_INET;
	_server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	_server_addr.sin_port = htons(atoi(port.c_str()));
	int reuse = 1; //为非零，即重用bind中的地址
	if(setsockopt(_fd_server, SOL_SOCKET,SO_REUSEADDR, &reuse, sizeof(int)) < 0) {
		std::cout << "setsocket ERROR!" << std::endl;
	}
	int i = bind(_fd_server, (struct sockaddr *)&_server_addr, sizeof(_server_addr));
	/*以下测试用*/
	if(i == -1) {
		std::cout << errno << std::endl;
	}
}

UDPserver::~UDPserver() {
	close(_fd_server);
}

ssize_t UDPserver::recvMsg(std::string &msg) {
	memset(_buf, 0, BUF_SIZE * sizeof(char));	
	memset(&_client_addr, 0, sizeof(_client_addr));
	socklen_t len = sizeof(_client_addr);
	recvfrom(_fd_server, _buf, 1024, 0, (struct sockaddr*)&_client_addr, &len);
	std::string temp(_buf, strlen(_buf)); 
	msg = temp;
	return msg.size();
}

ssize_t UDPserver::sendMsg(unint &ip, unint &port, cst &msg) {
	_client_addr.sin_family = AF_INET;
	_client_addr.sin_addr.s_addr = ip;
	_client_addr.sin_port = port;
	sendto(_fd_server, msg.c_str(), msg.size(), 0, (struct sockaddr *)&_client_addr, sizeof(_client_addr));
	return msg.size();
}

unsigned int UDPserver::getClientIp() {
	return _client_addr.sin_addr.s_addr;	
}

unsigned int UDPserver::getClientPort() {
	return _client_addr.sin_port;		
}



