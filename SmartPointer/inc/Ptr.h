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
