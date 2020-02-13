#include "base.h"

#include <iostream>

void Base::NameOf() {
  std::cout << "Base::NameOf" << std::endl;
}

void Base::InvokingClass() {
  std::cout << "Invoked by Base." << std::endl;
}
