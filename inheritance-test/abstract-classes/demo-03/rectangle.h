#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "shape.h"

class Rectangle : public Shape {
 public:
  Rectangle() {}
  Rectangle(double l, double w) : length_(l), width_(w) {}

 public:
  std::string NameOf() const override;
  double Area() const override;

 private:
  double length_;
  double width_;
};

#endif
