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
