/*************************************************************************
	> File Name: Ptr.h
	> Author: Kang
	> Mail:likang@tju.edu.cn 
	> Created Time: 2017年08月25日 星期五 10时05分30秒
 ************************************************************************/
#ifndef PTR_H_
#define PTR_H_

template< class T >
class Ptr {
public:
	// dereference object
	virtual T& operator*() = 0;

	// dereference object member
	virtual T* operator->() = 0;
};

#endif
