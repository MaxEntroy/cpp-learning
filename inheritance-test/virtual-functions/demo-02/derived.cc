#include "derived.h"

#include <iostream>

void Derived::NameOf() {
  std::cout << "Derived::Nameof" << std::endl;
}

void Derived::InvokingClass() {
  std::cout << "Invoked by Derived." << std::endl;
}
