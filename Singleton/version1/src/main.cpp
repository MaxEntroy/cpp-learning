/*************************************************************************
	> File Name: main.cpp
	> Author: Kang
	> Mail:likang@tju.edu.cn 
	> Created Time: 2017年08月03日 星期四 21时23分32秒
 ************************************************************************/
// main.cpp
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "DB.h"
#define THREADS_NUM 2

pthread_t tid_arr[THREADS_NUM];

void threads_init();
void threads_destroy();

void err_msg(int en, const char* msg);

void* thread_handle(void*);

int main( void ){

    threads_init();

    threads_destroy();

    exit( EXIT_SUCCESS );
}
void threads_init(){
    int ret;
    for(int i = 0; i < THREADS_NUM; ++i){
        ret = pthread_create( tid_arr + i, NULL, thread_handle, NULL );
        if( ret != 0 ){
            err_msg( ret, "pthread_create" );
        }
    }

}
void threads_destroy(){
    int ret;
    for( int i = 0; i < THREADS_NUM; ++i ){
        ret = pthread_join( tid_arr[i], NULL );
        if( ret != 0 ){
            err_msg( ret, "pthread_join" );
        }
    }
}

void err_msg(int en, const char* msg){
    errno = en;
    perror(msg);
    exit(EXIT_FAILURE);
}

void* thread_handle(void*) {
    std::cout << "-----------------" << pthread_self() << "------------------" << std::endl;

    DB* db = DB::create_db();
    sleep(3);
    std::cout << pthread_self() << " : " << db << std::endl;
    DB::destroy_db();

    std::cout << "-----------------" << pthread_self() << "------------------" << std::endl;
    return NULL;
}

