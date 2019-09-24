#include <iostream>

extern "C" {
#include "sub.h"
int cppsub(int a, int b) {
    std::cout << "cppsub called." << std::endl;
    return a - b;
}
}
