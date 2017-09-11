/*************************************************************************
	> File Name: DB.h
	> Author: Kang
	> Mail:likang@tju.edu.cn 
	> Created Time: 2017年08月03日 星期四 21时24分14秒
 ************************************************************************/
#ifndef DB_H_
#define DB_H_


// compile time 生成单例
#include <iostream>
#include <string>
#include <map>

class DB {
public:
    static DB* create_db(){
        return const_cast<DB*>(dbptr);
    }
    static void destroy_db(){
        if(dbptr){
            delete dbptr;
            dbptr = NULL;
        }
    }
protected:
    DB() { std::cout << "DB() called." << std::endl; }
    virtual ~DB() { std::cout << "~DB() called." << std::endl; }

    // No copying allowed
    DB(DB&);
    DB& operator=(DB&);

private:
    static DB* dbptr;
};

DB* DB::dbptr = new DB(); 

#endif
