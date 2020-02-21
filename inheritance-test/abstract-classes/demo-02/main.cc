#include "derived.h"

int main(void) {
  Base* p = new Derived();

  p->NameOf();

  delete p;
  return 0;
}
