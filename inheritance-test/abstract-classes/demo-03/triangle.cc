#include "triangle.h"

std::string Triangle::NameOf() const {
  return "Triangle";
}

double Triangle::Area() const {
  return 1.0/2 * length_ * height_;
}
