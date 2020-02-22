#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "shape.h"

class Triangle : public Shape {
 public:
  Triangle() {}
  Triangle(double l, double h) : length_(l), height_(h) {}

 public:
  std::string NameOf() const override;
  double Area() const override;

 private:
  double length_;
  double height_;
};

#endif
