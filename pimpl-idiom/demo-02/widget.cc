#include "widget.h"

namespace cl {

void Widget::Show() const {
  pimpl_->Show(*this);
}

} // namespace cl
