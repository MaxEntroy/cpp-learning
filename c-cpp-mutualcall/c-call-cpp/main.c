#include <stdio.h>

#include "add.h"
#include "sub.h"

int main(void) {
    int a = 3;
    int b = 4;

    int ret = cppadd(a, b);
    printf("cppadd: %d\n", ret);

    ret = cppsub(a, b);
    printf("cppsub: %d\n", ret);

    return 0;
}
