#ifndef BUTTON_H_
#define BUTTON_H_

#include "object.h"

class Button : virtual public Object {
 public:
  Button() : Object() {}
  virtual ~Button() {}
  virtual void NameOf() {std::cout << "This is a button." << std::endl;}
};

#endif
