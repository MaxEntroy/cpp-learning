#ifndef DERIVED_H_
#define DERIVED_H_

#include "base.h"

class Derived : public Base {
 public:
  Derived() : Base() {
    std::cout << "Derived() called.\n";
  }
  ~Derived() {
    std::cout << "~Derived() called.\n";
  }
};

#endif
