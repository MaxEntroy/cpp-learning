#include <iostream>

extern "C" {
#include "add.h"
#include "sub.h"
}

int main(void) {
    int a = 3;
    int b = 4;

    int ret = cadd(a, b);
    std::cout << "cadd: " << ret << std::endl;
    ret = csub(a, b);
    std::cout << "csub: " << ret << std::endl;

    return 0;
}
