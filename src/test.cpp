/**
 *
 * 测试用
 *
 *
 */

#include "../include/Threadpool.h"
#include "../include/Config.h"
#include "../include/UDPserver.h"
#include <string>
#include <cstdlib>
#include <iostream>


using namespace std;

int main(int argc, char *argv[]) {
	if(argc != 2) {
		return 1;
	}
	Config cfig(argv[1]);

	cout << cfig[0] << " " << cfig[1] << endl;
	UDPserver ser(cfig[0], cfig[1]);
	Threadpool thpool(cfig);
	//Threadpool thpool(8);
	thpool.start_threadpool();

	cout << "Server Started!" << endl;

	string temp;

	while(true) {
		ser.recvMsg(temp);	
		Task task;
		task.solve = temp;
		task.ip = ser.getClientIp();
		task.port = ser.getClientPort();


		//std::cout << "开始测试" << std::endl;
		//std::cout << temp << std::endl;
		
		thpool.add_task(task);
		thpool.get_task(task);
		
		ser.sendMsg(task.ip, task.port, task.solve);
	}

	return 0;
}
