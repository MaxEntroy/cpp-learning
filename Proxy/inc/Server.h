/*************************************************************************
	> File Name: Server.h
	> Author: Kang
	> Mail:likang@tju.edu.cn 
	> Created Time: 2017年08月03日 星期四 11时46分40秒
 ************************************************************************/
#ifndef SERVER_H_
#define SERVER_H_

class Server {
public:
	Server() {}
	virtual ~Server() {}
public:
	virtual void request() = 0;
};

#endif
