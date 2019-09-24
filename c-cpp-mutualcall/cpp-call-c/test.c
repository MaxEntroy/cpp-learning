#include <stdio.h>

#include "add.h"
#include "sub.h"

int main(void) {
    int a = 3;
    int b = 4;

    int ret = cadd(a, b);
    printf("cadd: %d\n", ret);
    ret = csub(a, b);
    printf("csub: %d\n", ret);

    return 0;
}
