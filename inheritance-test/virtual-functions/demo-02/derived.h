#ifndef DERIVED_H_
#define DERIVED_H_

#include "base.h"

class Derived : public Base {
 public:
  Derived() : Base() {}

  virtual void NameOf();
  void InvokingClass();

};

#endif
