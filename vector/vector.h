#ifndef VEC_H_
#define VEC_H_
#include <memory>
#include <utility>

namespace ACC {

template<class T> 
class vector{

public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;
	typedef std::size_t size_type;

public:
	vector(){create();};
	explicit vector(int n, const T& val = T()){ create( n, val ); };
	vector( const vector& rhs ){ create( rhs.begin(), rhs.end() ); }
	vector& operator=( const vector& rhs );
	~vector(){ uncreate(); }

public:
	size_type size() const { return avail - data; }
	
	T& operator[]( size_type i ) { return data[i]; }
	const T& operator[]( size_type i ) const  { return data[i]; }
	
	iterator begin()  { return data; }
	const_iterator begin() const { return data; }
	iterator end()  { return avail; }
	const_iterator end() const { return avail; }

	void push_back(const T& val) {
		if( avail == limit )
			grow();
		unchecked_append(val);
	}

private:
	T* data;
	T* avail;
	T* limit;
private:
	void create(){ data = avail = limit = 0; }
	void create( int n, T val);
	void create( const_iterator b, const_iterator e ); 
	void uncreate();
private:
	std::allocator<T> alloc;
	void grow();
	void unchecked_append(const T& val);
};// vector

template<class T>
vector<T>& vector<T>::operator=( const vector& rhs ) {
	if( this != &rhs ){
		uncreate();
		create(rhs.begin(), rhs.end());
	}
	return *this;
}

template<class T>
void vector<T>::create( int n, T val ) {
	data = alloc.allocate(n);
	avail = limit = data+n;
	std::uninitialized_fill( data, avail, val );
}

template<class T>
void vector<T>::create( const_iterator b, const_iterator e ){
	data = alloc.allocate(e - b);
	avail = limit = std::uninitialized_copy( b, e, data );
}

template<class T>
void vector<T>::uncreate() {
	if( data ){
		iterator it = avail;
		while( it != data ){
			alloc.destroy(--it);
		}
		
		alloc.deallocate(data, limit-data);
	}
	data = avail = limit = 0;
}

template<class T>
void vector<T>::grow() {
	size_type new_size = std::max( 2*(limit - data), std::ptrdiff_t(1) );
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = std::uninitialized_copy( data, avail, new_data );
	iterator new_limit = new_data + new_size;

	uncreate();

	data = new_data;
	avail = new_avail;
	limit = new_limit;
}

template<class T>
void vector<T>::unchecked_append( const T& val ) {
	alloc.construct(avail++, val);
}

}// namespace ACC

#endif // VEC_H_
