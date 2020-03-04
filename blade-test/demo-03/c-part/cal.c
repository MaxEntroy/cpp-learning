#include "cal.h"

#include <stdio.h>

int add(int left, int right) {
  if(left < 0 || right < 0) {
    fprintf(stderr, "Can only add positive numbers, received %d and %d\n", left, right);
    return -1;
  }

  if(!left || !right)
    return 0;

  return left + right;
}
