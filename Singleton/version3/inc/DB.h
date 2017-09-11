/*************************************************************************
	> File Name: DB.h
	> Author: Kang
	> Mail:likang@tju.edu.cn 
	> Created Time: 2017年08月03日 星期四 21时25分46秒
 ************************************************************************/
#ifndef DB_H_
#define DB_H_

// static 单例
// 自动进行垃圾回收
#include <iostream>

class DB {
public:

    static DB* create_db(){
        static DB db;
        return &db;
    }

protected:
    DB() { std::cout << "DB() called." << std::endl; } 
    virtual ~DB() { std::cout << "~DB() called." << std::endl; } 

    DB( const DB& rhs );
    DB& operator=( const DB& rhs );

};

#endif
