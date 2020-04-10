[TOC]
## 禁止copying and assigning

这一小节讨论一下禁止拷贝和赋值语义的几种写法

### DISALLOW_COPY_AND_ASSIGN

```cpp
// foo.h
#ifndef FOO_H_
#define FOO_H_

namespace test {

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  TypeName& operator=(const TypeName&);

class Bar;

class Foo {
 public:
  Foo() : val_(0) {}

  void Print();

  friend Bar;
 private:
  DISALLOW_COPY_AND_ASSIGN(Foo)
  int val_;
};

} // namespace test

#endif // FOO_H_

// foo.cc
#include "foo.h"

#include <iostream>

namespace test {

void Foo::Print() {
  std::cout << "Foo::Print() called.\n";
}

} // namespace test

// bar.h
#ifndef BAR_H_
#define BAR_H_


#include "foo.h"

namespace test {

class Bar {
 public:
  Bar() {}

  void DoSomething();
};

} // namespace test

#endif // BAR_H_

// bar.cc
#include "bar.h"

#include <iostream>

namespace test {

void Bar::DoSomething() {
  Foo a;
  std::cout << a.val_ << std::endl;

  Foo b(a);

  Foo c;
  c = a;
}

} // namespace test

// main.cc
#include "bar.h"

using namespace test;

// void test_foo() {
//   Foo a, b;
//
//   Foo c(a);
//   b = a;
// }

int main(void) {
  Bar bar;
  bar.DoSomething();
  return 0;
}

/*
compilation阶段没有暴露问题
g++ -c bar.cc

linking阶段暴露
/home/kang/tmp/cpp-test/normal_test/demo/bar.cc:11: undefined reference to `test::Foo::Foo(test::Foo const&)'
/home/kang/tmp/cpp-test/normal_test/demo/bar.cc:14: undefined reference to `test::Foo::operator=(test::Foo const&)'
*/
```

q:这种写法有什么问题吗?
>因为copying and assigning声明为private，类外的拷贝的赋值语义被禁止。
但是对于自身成员函数，和friend的访问，private并不起作用。
所以，我们知道compile time大致上可以分两个阶段，compilation and linking，
compilation阶段，这个问题并不会暴露，而是到了linking阶段，这个问题才会出现。
虽然，最终问题还是暴露了，但是我们还是希望能尽可能早的暴露问题。具体问题是，copying constructor and assignment operator这两个函数没有定义。

### Noncopyable class

针对上面的问题，尝试用继承的方式解决。

q:如何解决?
>尝试拷贝Foo对象时，编译器便试着生成一个copy构造函数和一个copy assignment操作符.
编译器自动生成这些函数时，会调用其基类的对应函数，而基类中这些函数是private，因而那些调用会被编译器拒绝，产生编译器错误。
>
所以，这个办法的好处是，只要有拷贝或者赋值的场景，就会触发上述机制，导致compilation失败，从而解决了上面说的问题。

q:这种方法除了解决disallow宏所解决不了的问题，还有什么优点?
>像Noncopyable这样的基类，没有non-static成员变量，没有virtual函数，也没有virtual base classes，可以满足空白基类最优化的条件(empty base optimization)
这类基类的派生类，不会继承的关系而产生多余的空间存储

q:这种方法有什么缺点?
>这种方法的缺点就是empty base class的缺点

```cpp
#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_

namespace test {

class NonCopyable {
 protected:
  NonCopyable() {}
  virtual ~NonCopyable() {}

 private:
  NonCopyable(const NonCopyable&);
  NonCopyable& operator=(const NonCopyable&);
};

} // namespace test

#endif // NONCOPYABLE_H_
```

### delete function

q:delete function如何解决以上两种方法的缺点？
>1. delete function不使用继承，自然不会产生ebo的问题
2. delete function的特殊性，使得compilation 阶段使用delete function会报错。第一种方法中，private方法并不是delete function，所以compilation阶段使用没问题，linking阶段才发现没有定义。

```cpp
#ifndef FOO_H_
#define FOO_H_

namespace test {

class Bar;

class Foo {
 public:
  Foo() : val_(0) {}
  Foo(const Foo&) = delete;
  Foo& operator=(const Foo&) = delete;

 public:
  void Print();
  friend Bar;

 private:
  int val_;
};

} // namespace test

#endif // FOO_H_
```

参考<br>
[【C++】DISALLOW_COPY_AND_ASSIGN](https://www.cnblogs.com/dwdxdy/archive/2012/07/16/2594113.html)<br>
[Defaulted and Deleted Functions](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2346.htm)<br>
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html#Copyable_Movable_Types)<br>