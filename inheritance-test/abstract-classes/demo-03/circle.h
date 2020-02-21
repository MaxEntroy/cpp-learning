#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "shape.h"

class Circle : public Shape {
 public:
  Circle() {}
  explicit Circle(double r) : radius_(r) {}

 public:
  virtual std::string NameOf() const;
  virtual double Area() const;

 private:
  double radius_;
};

#endif
