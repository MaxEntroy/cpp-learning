#include "circle.h"

#include <math.h>

const double PI = atan(1.0) * 4;

std::string Circle::NameOf() const {
  return "Circle";
}

double Circle::Area() const {
  return PI * radius_ * radius_;
}
