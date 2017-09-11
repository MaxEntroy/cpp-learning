/*************************************************************************
	> File Name: Pointer.h
	> Author: Kang
	> Mail:likang@tju.edu.cn 
	> Created Time: 2017年08月25日 星期五 10时07分39秒
 ************************************************************************/
#ifndef POINTER_H_
#define POINTER_H_
#include <iostream>
#include "Ptr.h"

template< class T >
class Pointer : public Ptr<T> {
public:
	Pointer() : ptr_(NULL), ref_cnt_(0) {}
	explicit Pointer( T* pp ) : ptr_(pp), ref_cnt_(1) {}
	virtual ~Pointer() { release_ref(); }
public:
	void add_ref() { ref_cnt_++; }
	void release_ref() { 
		ref_cnt_--;
		if(!ref_cnt_){ 
			delete ptr_; 
			ptr_ = NULL; 
		}
	}
	int get_ref() const { return ref_cnt_; }

	T* get() const { return ptr_; }
public:
	T& operator*()  { return *ptr_; }
	T* operator->() { return ptr_; }
private:
	// No copying allowed
	Pointer( const Pointer& );
	void operator=( const Pointer& );
private:
	T* ptr_;
	int ref_cnt_;
};


#endif
