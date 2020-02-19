#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>

class Object {
 public:
  Object() {}
  virtual ~Object() {}

  virtual void NameOf() {std::cout << "This is an object." << std::endl;}
};

#endif
