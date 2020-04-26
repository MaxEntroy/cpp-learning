#ifndef IMPL_H_
#define IMPL_H_

namespace cl {

class Widget;

class impl {
 public:
  impl() : data_(0) {}
  impl(int d) : data_(d) {}

  void Show(const Widget&) const;

 private:
  int data_;
};

} // nmespace cl

#endif // IMPL_H_
