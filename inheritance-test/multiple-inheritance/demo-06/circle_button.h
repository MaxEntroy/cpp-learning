#include "circle.h"
#include "button.h"

class CircleButton : public Circle, public Button {
 public:
  CircleButton() : Circle(), Button() {}
  void NameOf();
};
