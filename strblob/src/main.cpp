#include <iostream>
#include "StrBlob.h"
int main() { 

    StrBlob str_list = { "kang", "lucy", "xin" };
    int sz = str_list.size();
    std::cout << "str_list:" << std::endl;
    for( int i = 0; i < sz; ++i ){
        std::cout << str_list[i] << std::endl;
    }

    StrBlob str_list_copy = str_list;
    sz = str_list_copy.size();
    std::cout << "str_list_copy:" << std::endl;
    for( int i = 0; i < sz; ++i ){
        std::cout << str_list_copy[i] << std::endl;
    }

    str_list_copy.push_back( "hello,world" );

    std::cout << "----------after copy---------- " << std::endl;

    sz = str_list.size();
    std::cout << "str_list:" << std::endl;
    for( int i = 0; i < sz; ++i ){
        std::cout << str_list[i] << std::endl;
    }

    sz = str_list_copy.size();
    std::cout << "str_list_copy:" << std::endl;
    for( int i = 0; i < sz; ++i ){
        std::cout << str_list_copy[i] << std::endl;
    }

    return 0; 
}
