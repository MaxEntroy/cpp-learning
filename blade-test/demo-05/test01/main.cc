#include <iostream>
#include "foo.h"

using namespace bt;

int main() {
  Foo foo;
  std::cout << foo.GetX() << std::endl;
  return 0;
}
