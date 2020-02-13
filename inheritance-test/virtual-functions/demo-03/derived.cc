#include "derived.h"

#include <iostream>

Derived::~Derived() {
  std::cout << "Deleting Derived." << std::endl;
}

void Derived::NameOf() {
  std::cout << "Derived::Nameof" << std::endl;
}

void Derived::InvokingClass() {
  std::cout << "Invoked by Derived." << std::endl;
}
