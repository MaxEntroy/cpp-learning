#ifndef FOO_H_
#define FOO_H_

#include "noncopyable.h"

namespace test {


class Bar;

class Foo : public NonCopyable {
 public:
  Foo() : val_(0) {}

  void Print();

  friend Bar;
 private:
  int val_;
};

} // namespace test

#endif // FOO_H_
