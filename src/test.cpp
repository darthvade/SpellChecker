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

using namespace std;

int main(int argc, char *argv[]) {
	if(argc != 2) {
		return 1;
	}
	Config cfig(argv[1]);

	UDPserver ser(cfig[0], cfig[1]);
	Threadpool thpool(8);
	thpool.start_threadpool();

	string temp;

	while(true) {
		ser.recvMsg(temp);	
		Task task;
		task.solve = temp;
		task.ip = ser.getClientIp();
		task.port = ser.getClientPort();
		thpool.add_task(task);
		thpool.get_task(task);
		ser.sendMsg(task.ip, task.port, task.solve);
	}

	return 0;
}
