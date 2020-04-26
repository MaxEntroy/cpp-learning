#include "impl.h"
#include "widget.h"

#include <iostream>

namespace cl {

void impl::Show(const Widget& w) const {
  if(w.IsShown()) {
    std::cout << "data: " << data_ << std::endl;
  }
}

} // namespace cl
