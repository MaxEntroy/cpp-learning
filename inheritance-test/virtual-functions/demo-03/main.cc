#include <iostream>

#include "base.h"
#include "derived.h"

int main(void) {

  Base* p_base = new Derived();       // 动态调用 dynamic type checking 异常析构，资源泄露
  Derived* p_derived = new Derived(); // 静态调用 static type checking 正常析构
  Derived a_derived;                  // 静态调用 static type checking 正常熊沟

  delete p_base;
  std::cout << "-------------" << std::endl;
  delete p_derived;
  std::cout << "-------------" << std::endl;

  return 0;
}
