#ifndef WIDGET_H_
#define WIDGET_H_

#include <memory>

namespace cl {

class Widget {
 public:
  Widget();
  Widget(int n);
  ~Widget();

  Widget(const Widget&) = delete;
  Widget& operator=(const Widget&) = delete;

  Widget(Widget&&) = default;
  Widget& operator=(Widget&&) = default;


  bool IsShown() const {return true;}
  void Show() const;

 private:
  class impl;
  std::unique_ptr<impl> pimpl_;

};

} // namespace

#endif // WIDGET_H_
