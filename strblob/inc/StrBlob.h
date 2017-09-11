#ifndef STRBLOB_H_
#define STRBLOB_H_

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <stdexcept>

class StrBlob {
public:

    StrBlob() : data( std::make_shared< std::vector< std::string> >() ) {}
    StrBlob( const std::initializer_list< std::string  >& il ) : data( std::make_shared< std::vector< std::string > >(il) ) {}
public:
    typedef std::vector<std::string>::size_type size_type;
    typedef std::vector<std::string>::iterator iterator;

public:
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    iterator begin() { return data->begin(); }
    iterator end() { return data->end(); }

    void push_back( const std::string& s ) { data->push_back(s); }
    void pop_back() { 
        check( 0, "empty strblob" );
        data->pop_back(); 
    }
public:
    std::string& front() { 
        check( 0, "empty strblob" );
        return data->front(); 
    }
    const std::string& front() const { 
        check( 0, "empty strblob" );
        return data->front(); 
    }
    std::string& back() { 
        check( 0, "empty strblob" );
        return data->back(); 
    }
    const std::string& back() const { 
        check( 0, "empty strblob" );
        return data->back(); 
    }
public:
    std::string& operator[]( size_type i ) { 
        check( i, "out of range" );
        return (*data)[i]; 
    }
    const std::string& operator[]( size_type i ) const {
        check( i, "out of range" );
        return (*data)[i];
    }
private:
    void check( size_type i, const std::string& err ) const {
        if( i >= data->size() )
            throw std::out_of_range( err );
    }

private:    
    std::shared_ptr< std::vector<std::string> > data;
};

#endif

