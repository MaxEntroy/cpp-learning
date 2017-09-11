/*************************************************************************
	> File Name: DB.h
	> Author: Kang
	> Mail:likang@tju.edu.cn 
	> Created Time: 2017年08月03日 星期四 21时22分47秒
 ************************************************************************/
// DB.h
#ifndef DB_H_
#define DB_H_
#include <iostream>
#include <assert.h>
#include <pthread.h>

class DB {
public:
    static DB* create_db(){

        if( !dbptr ){ // double check

            pthread_mutex_lock(&mut); // lock

            if(!dbptr){

                dbptr = new DB();
                assert( dbptr );
            }

            pthread_mutex_unlock(&mut); // unlock
        }


        return dbptr;
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
    DB(const DB& rhs);
    DB& operator=( const DB& rhs );

private:
    static DB* dbptr;
    static pthread_mutex_t mut;
};
DB* DB::dbptr = NULL;
pthread_mutex_t DB::mut = PTHREAD_MUTEX_INITIALIZER;

#endif
