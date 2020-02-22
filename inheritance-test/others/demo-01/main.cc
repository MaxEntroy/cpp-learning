#include "derived.h"

int main() {
  Base* p = new Derived();

  p->NameOf();

  delete p;
  return 0;
}
