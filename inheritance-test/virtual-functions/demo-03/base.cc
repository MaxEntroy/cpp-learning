#include "base.h"

#include <iostream>

Base::~Base() {
  std::cout << "Deleting Base." << std::endl;
}

void Base::NameOf() {
  std::cout << "Base::NameOf" << std::endl;
}

void Base::InvokingClass() {
  std::cout << "Invoked by Base." << std::endl;
}
