#include <iostream>
#include "thirdparty/tmath/include/tmath/tmath.h"

int main(void) {

    int left = 3;
    int right = 4;
    int ret = TAdd(left, right);
    std::cout << "TAdd: " << ret << std::endl;

    ret = TMinus(left, right);
    std::cout << "TMinus: " << ret << std::endl;

    return 0;
}
