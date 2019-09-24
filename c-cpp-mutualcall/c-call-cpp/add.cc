#include <iostream>

extern "C" {
#include "add.h"
int cppadd(int a, int b) {
    std::cout << "cppadd called." << std::endl;
    return a + b;
}
}
