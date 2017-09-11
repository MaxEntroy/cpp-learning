/*************************************************************************
	> File Name: RealServer.h
	> Author: Kang
	> Mail:likang@tju.edu.cn 
	> Created Time: 2017年08月03日 星期四 11时49分46秒
 ************************************************************************/
#ifndef REAL_SERVER_H_
#define REAL_SERVER_H_
#include <iostream>
#include "Server.h"

class RealServer : public Server {
public:
	RealServer() {};
	virtual ~RealServer() {}
public:
	virtual void request() {
		std::cout << "RealServer request." << std::endl;
	}
};

#endif
