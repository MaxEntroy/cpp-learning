#include <iostream>

#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

void ShowArea(Shape* p);

int main(void) {
  Circle cir(1.0);
  Triangle tri(1.0, 1.0);
  Rectangle rec(1.0, 1.0);

  ShowArea(&cir);
  ShowArea(&tri);
  ShowArea(&rec);

  return 0;
}

void ShowArea(Shape* p) {
  std::cout << p->NameOf() << ":" << p->Area() << std::endl;
}
