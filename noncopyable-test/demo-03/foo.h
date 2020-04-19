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
