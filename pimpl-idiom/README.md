## Pimpl-idiom

### 实现

q:why pimpl-idiom?
>没有看的非常仔细，但是有一点是确定的。就是compilation firewall.
避免头文件当中的private interface接口变化，导致header重新编译，由于header重新编译时，会导致include的文件全部都重新编译，增加额外的编译时间。
当然 ，gtest里面也通过这种手法来对private interface进行测试。
>
>不过，目前没有看到实际的项目在用这种手法，当然我也没看很多，起码leveldb里面还是正常的private interface.

q: 一些需要注意的点：
1. destructor,需要在implemetation进行实现，他需要看到class impl的完整实现. 所以，在header file中需要显示声明destructor。根据rule of 3(5). 其余对象管理函数也需要显示声明。根据语义，保留了move semantics, 禁止了copy semantics.
2. 如果class impl需要外部类的方法和成员，需要保留对外部类的引用(指针)
3. 构造当中其实暴露了impl的数据成员，但是没办法

```cpp
// widget.h
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

// widget.cc
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
```

## 实践

- demo-01

这个就是上文描述的实现,主要参考了cpp-reference的实现

- demo-02

这个是pimpl抽出来了，为了让这个模块能够进行单元测试，这么做认为也是可以的，gtest给出了这么做的建议

参考<br>
[The C++ Pimpl](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/the-c-pimpl-r1794/)<br>
[PImpl](https://en.cppreference.com/w/cpp/language/pimpl)<br>
[Compilation Firewalls](https://herbsutter.com/gotw/_100/)<br>
[The PIMPL idiom](https://cpppatterns.com/patterns/pimpl.html)
[Pimpl Idiom /handle body idiom](https://www.cnblogs.com/youxin/p/4300797.html)
