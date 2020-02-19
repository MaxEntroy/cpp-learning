#ifndef CIRCLE_BUTTON_H_
#define CIRCLE_BUTTON_H_

#include "circle.h"
#include "button.h"

class CircleButton : public Circle, public Button {
 public:
  CircleButton() : Circle(), Button() {}
  virtual ~CircleButton() {}
  virtual void NameOf() {std::cout << "This is a circle button." << std::endl;}
};

#endif
