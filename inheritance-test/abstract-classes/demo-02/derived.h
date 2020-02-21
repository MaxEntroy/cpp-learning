#ifndef DERIVED_H_
#define DERIVED_H_

#include "base.h"

class Derived : public Base {
 public:
  Derived() {std::cout << "Derived() called.\n";}
  ~Derived() {std::cout << "~Derived() called.\n";}

  virtual void NameOf() {
    std::cout << "This is a derived class.\n";
  }
};

#endif
