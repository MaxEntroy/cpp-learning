#include <iostream>

#include "common.h"

int main(void) {

  int l1 = 1;
  int l2 = -3;
  std::cout << max(l1, l2) << std::endl;

  double d1 = 3.2;
  double d2 = -1.3;
  std::cout << max(d1, d2) << std::endl;

  return 0;
}
