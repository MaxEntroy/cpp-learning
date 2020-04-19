#include "bar.h"

#include <iostream>

namespace test {

void Bar::DoSomething() {
  Foo a;
  std::cout << a.val_ << std::endl;

  Foo b(a);

  Foo c;
  c = a;
}

} // namespace test
