#include "circle.h"
#include "button.h"

class CircleButton : public Circle, public Button {
 public:
  CircleButton() : Object(), Circle(), Button() {}
};
