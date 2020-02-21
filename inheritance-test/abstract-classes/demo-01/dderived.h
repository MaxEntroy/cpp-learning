#ifndef DDERIVED_H_
#define DDERIVED_H_

#include "derived.h"

class DDerived : public Derived {
 public:
  DDerived() : Derived() {
    std::cout << "DDerived() called.\n";
  }
  ~DDerived() {
    std::cout << "~DDerived() called.\n";
  }
};

#endif
