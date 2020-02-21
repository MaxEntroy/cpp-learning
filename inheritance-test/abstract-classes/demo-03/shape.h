#ifndef SHAPE_H_
#define SHAPE_H_

#include <string>

class Shape {
 public:
  virtual ~Shape() {}

 public:
  virtual std::string NameOf() const = 0;
  virtual double Area() const = 0;
};

#endif
