#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "shape.h"

class Circle : public Shape {
 public:
  Circle() {}
  explicit Circle(double r) : radius_(r) {}

 public:
  std::string NameOf() const override;
  double Area() const override;

 private:
  double radius_;
};

#endif
