#include "rectangle.h"

std::string Rectangle::NameOf() const {
  return "Rectangle";
}

double Rectangle::Area() const {
  return length_ * width_;
}
