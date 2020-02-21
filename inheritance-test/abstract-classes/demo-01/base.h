#ifndef BASE_H_
#define BASE_H_

#include <iostream>

class Base {
 public:
  Base() {std::cout << "Base() called.\n";}
  virtual ~Base() {std::cout << "~Base() called.\n";}
};

#endif
