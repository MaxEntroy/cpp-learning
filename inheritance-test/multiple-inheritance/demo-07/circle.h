#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "object.h"

class Circle : virtual public Object {
 public:
  Circle() {}
  void NameOf() {std::cout << "This is a circle" << std::endl;}
};

#endif
