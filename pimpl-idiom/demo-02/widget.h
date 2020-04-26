#ifndef WIDGET_H_
#define WIDGET_H_

#include <memory>

#include "impl.h"

namespace cl {

class Widget {
 public:
  Widget() : pimpl_(new impl()) {}
  Widget(int n) : pimpl_(new impl(n)) {}

  Widget(const Widget&) = delete;
  Widget& operator=(const Widget&) = delete;

  bool IsShown() const {return true;}
  void Show() const;

 private:
  std::unique_ptr<impl> pimpl_;

};

} // namespace

#endif // WIDGET_H_
