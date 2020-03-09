#include "cal.h"

#include <iostream>

int add(int left, int right) {
  if(left < 0 || right < 0) {
    std::cerr << "Can only add positive number, received "
      << left << " and " << right << std::endl;
    return -1;
  }

  if(!left || !right)
    return 0;

  return left + right;
}
