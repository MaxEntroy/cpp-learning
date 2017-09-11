/*************************************************************************
	> File Name: main.cpp
	> Author: Kang
	> Mail:likang@tju.edu.cn 
	> Created Time: 2017年08月03日 星期四 21时25分06秒
 ************************************************************************/
#include <iostream>
#include "DB.h"

int main(){

    DB* db1 = DB::create_db();
    DB* db2 = DB::create_db();

    std::cout << db1 << std::endl;
    std::cout << db2 << std::endl;

    DB::destroy_db();
    return 0;
}

