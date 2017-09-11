/*************************************************************************
	> File Name: ProxyServer.h
	> Author: Kang
	> Mail:likang@tju.edu.cn 
	> Created Time: 2017年08月03日 星期四 11时50分37秒
 ************************************************************************/
#ifndef PROXY_SERVER_H_
#define PROXY_SERVER_H_
#include <iostream>
#include <memory>
#include "Server.h"
#include "RealServer.h"

class ProxyServer : public Server {
public:
	ProxyServer() {}
	virtual ~ProxyServer() {}
public:
	virtual void request() {
		std::cout << "ProxyServer request." << std::endl;
		
		// construct a real server
		if( !p_realserver ){
			p_realserver = std::unique_ptr<RealServer>( new RealServer() ) ; // move semantics
		}
		p_realserver->request();
	}
private:
	std::unique_ptr< RealServer > p_realserver;
};

#endif
