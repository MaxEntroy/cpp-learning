#ifndef DERIVED_H_
#define DERIVED_H_

#include "base.h"

class Derived : public Base {
 public:
  Derived() : Base() {}
  ~Derived();

  virtual void NameOf();
  void InvokingClass();

};

#endif
