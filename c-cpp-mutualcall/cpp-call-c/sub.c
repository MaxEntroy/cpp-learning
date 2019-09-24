#include <stdio.h>
#include "sub.h"

int csub(int a, int b) {
    printf("c func: csub called.\n");
    return a - b;
}
