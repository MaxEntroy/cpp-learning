#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "shape.h"

class Triangle : public Shape {
 public:
  Triangle() {}
  Triangle(double l, double h) : length_(l), height_(h) {}

 public:
  virtual std::string NameOf() const;
  virtual double Area() const;

 private:
  double length_;
  double height_;
};

#endif
