/**
 * UDPserver类
 * 说明：使用UDP发送接受消息
 */

#ifndef __UDPSERVER_H__
#define __UDPSERVER_H__

#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <cstdlib>

#define BUF_SIZE 1024

class UDPserver {
public:
	typedef const std::string cst;
	typedef unsigned int unint;
	UDPserver(cst &ip, cst &port);
	~UDPserver();
	ssize_t recvMsg(std::string &msg); //服务器接受消息
	ssize_t sendMsg(unint &ip, unint &port, cst &msg); //服务器按地址发送消息
	unsigned int getClientIp(); //取得客户端Ip  *注：返回其网络字节序
	unsigned int getClientPort(); //取得客户端Port  *注：返回其网络字节序
private:
	int _fd_server; //服务器socket
	struct sockaddr_in _server_addr; //服务端信息
	struct sockaddr_in _client_addr; //客户端信息
	char _buf[BUF_SIZE]; //服务器缓冲区
};

#endif
