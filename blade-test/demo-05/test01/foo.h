#ifndef FOO_H_
#define FOO_H_

#ifdef MYTEST
#define private public
#endif

namespace bt {

class Foo {
 public:
  Foo() : x(0) {}
 private:
  int GetX() const;
  int x;
};

} // namespace bt

#endif // FOO_H_
