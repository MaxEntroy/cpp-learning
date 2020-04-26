#include "widget.h"

#include <iostream>

namespace cl {

class Widget::impl {
 public:
  impl() : data_(0) {}
  impl(int d) : data_(d) {}

  void Show(const Widget& w) const {
    if(w.IsShown()) {
      std::cout << "data: " << data_ << std::endl;
    }
  }

 private:
  int data_;
};

Widget::Widget() : pimpl_(new impl()) {}

Widget::Widget(int n) : pimpl_(new impl(n)) {}

Widget::~Widget() = default;

void Widget::Show() const {
  pimpl_->Show(*this);
}

} // namespace cl
