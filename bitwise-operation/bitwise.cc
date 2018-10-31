#include "bitwise.h"

unsigned int rotate_left(unsigned int value, int n, int s) {
    return value >> (n-s) | value << s;
}
