#include "bitwise.h"

unsigned int rotate_left(unsigned int value, unsigned int n, unsigned int s) {
    return value >> (n-s) | value << s;
}
