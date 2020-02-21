#ifndef BASE_H_
#define BASE_H_

#include <iostream>

class Base {
 public:
  virtual ~Base() {std::cout << "~Base() called.\n";}
  virtual void NameOf() = 0;
};

#endif
