#include "dderived.h"

int main(void) {
  Base* p = new DDerived();
  std::cout << "hello,world!\n";

  delete p;
  return 0;
}
