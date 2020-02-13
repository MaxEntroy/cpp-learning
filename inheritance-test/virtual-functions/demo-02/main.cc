#include "base.h"
#include "derived.h"

int main(void) {
  Derived a_derived;
  Base* pbase = &a_derived;

  pbase->NameOf();
  pbase->InvokingClass();

  return 0;
}
