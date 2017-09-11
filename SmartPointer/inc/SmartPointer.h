#ifndef SMART_POINTER_H_
#define SMART_POINTER_H_
#include <iostream>
#include <assert.h>
#include "Ptr.h"
#include "Pointer.h"	

template< class T >
class SmartPointer : public Ptr<T> {
public:
	SmartPointer() : ppointer_(NULL) {}
	explicit SmartPointer( T* pp ) {
		ppointer_ = new Pointer<T>(pp);
		assert(ppointer_);
	}
	SmartPointer( const SmartPointer<T>& rhs ){ 
		ppointer_ = rhs.ppointer_;
		assert(ppointer_);
		ppointer_->add_ref();
	}
	void operator=( const SmartPointer<T>& rhs ){
		if( this != &rhs ){
			assert(ppointer_);
			ppointer_->release_ref();

			ppointer_ = rhs.ppointer_;
			assert(ppointer_);
			ppointer_->add_ref();
		}
	}
	virtual ~SmartPointer(){
		if(ppointer_){
			ppointer_->release_ref();
		}
	}
public:
	T& operator*() { 
		assert( ppointer_ );
		return ppointer_->operator*();
	}
	T* operator->() {
		assert( ppointer_ );
		return ppointer_->operator->();
	}
public:
	T* get() const {
		assert( ppointer_ );
		return ppointer_->get();
	}
	int use_count() const {
		assert( ppointer_ );
		return ppointer_->get_ref();
	}
public:
	operator bool() const { return ppointer_ != NULL; }
	bool operator==( const T* p_rhs ) const { 
		assert( ppointer_ );
		return ppointer_->get() == p_rhs;
	}
	bool operator==( const SmartPointer<T>& rhs ) const {
		assert(ppointer_);
		return ppointer_->get() == rhs.get();
	}
	bool operator!=( const T* p_rhs ) const {
		return !operator==(p_rhs);
	}
	bool operator!=( const SmartPointer<T>& rhs ) const {
		return !operator==(rhs);
	}
private:
	Pointer<T>* ppointer_;
};

#endif
