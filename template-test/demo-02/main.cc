#include <iostream>
#include <utility>

namespace version1 {

template<typename F, typename T1, typename T2>
void flip(F f, T1 t1, T2 t2) {
  f(t1, t2);
}

void f(int v1, int& v2) {
  v1 *= 2;
  v2 *= 2;
  std::cout << "[Internal]v1 = " << v1 << ", v2 = " << v2 << std::endl;
}

void test() {
  int v1 = 8, v2 = 16;
  f(v1, v2);
  std::cout << "[External]v1 = " << v1 << ", v2 = " << v2 << std::endl;

  flip(f, v1, v2);
  std::cout << "[External]v1 = " << v1 << ", v2 = " << v2 << std::endl;
}

// v2 is a reference, but the type of t2 is a plain type(int).

}  // namespace version1

namespace version2 {

template<typename F, typename T1, typename T2>
void flip(F f, T1& t1, T2& t2) {
  f(t1, t2);
}

void f(int v1, int& v2) {
  v1 *= 2;
  v2 *= 2;
  std::cout << "[Internal]v1 = " << v1 << ", v2 = " << v2 << std::endl;
}

void test() {
  int v1 = 8, v2 = 16;

  f(v1, v2);
  std::cout << "[External]v1 = " << v1 << ", v2 = " << v2 << std::endl;

  flip(f, v1, v2);
  std::cout << "[External]v1 = " << v1 << ", v2 = " << v2 << std::endl;

  //flip(f, v1, 5);  //  error
}

// based o version1, we make T2 a reference type, so the type of t2 is a reference type(int&)
// but, we can't bind a rvalue to a lvalue reference to a template type parameter

}  // namespace version2

namespace version3 {

template<typename F, typename T1, typename T2>
void flip(F f, T1&& t1, T2&& t2) {
  f(t1, t2);
}

void f(int v1, int& v2) {
  v1 *= 2;
  v2 *= 2;
  std::cout << "[Internal]v1 = " << v1 << ", v2 = " << v2 << std::endl;
}

void test() {
  int v1 = 8, v2 = 16;
  f(v1, v2);
  std::cout << "[External]v1 = " << v1 << ", v2 = " << v2 << std::endl;

  flip(f, v1, v2);  // flip(F, int&, int&) type of t1 is int&, type of t2 is int&. Be careful, T1 is int&, not the type of v1. T1&& is the type of t1.
  std::cout << "[External]v1 = " << v1 << ", v2 = " << v2 << std::endl;

  flip(f, v1, 5);  // flip(F, int&, int&&) type of t1 is int&, type of t2 is int&&
  std::cout << "[External]v1 = " << v1 << std::endl;
}

// We make T1, T2 a rvalue reference to a template type, which preserves the constness and lvalue/rvalue property of its corresponding argument.

}  // namespace version3

namespace version4 {

template<typename F, typename T1, typename T2>
void flip(F f, T1&& t1, T2&& t2) {
  f(t1, t2);
}

void g(int&& v1, int& v2) {
  v1 *= 2;
  v2 *= 2;
  std::cout << "[Internal]v1 = " << v1 << ", v2 = " << v2 << std::endl;
}

void test() {
  int v1 = 8, v2 = 16;
  g(std::move(v1), v2);
  std::cout << "[External]v1 = " << v1 << ", v2 = " << v2 << std::endl;

  // flip(g, 5, v2); // error
}

// t1 is a variable, which type is rvalue reference.
// t1 is a variable which means it is a lvalue
// the type of t1 is rvalue reference which means the nature of t1 is a rvalue

}  // namespace version4

namespace version5 {

template<typename F, typename T1, typename T2>
void flip(F f, T1&& t1, T2&& t2) {
  f(std::forward<T1>(t1), std::forward<T2>(t2));
}

void g(int&& v1, int& v2) {
  v1 *= 2;
  v2 *= 2;
  std::cout << "[Internal]v1 = " << v1 << ", v2 = " << v2 << std::endl;
}

void test() {
  int v1 = 8, v2 = 16;
  g(std::move(v1), v2);
  std::cout << "[External]v1 = " << v1 << ", v2 = " << v2 << std::endl;

  flip(g, 5, v2);
  //5 is rvalue,   T1 = int,  std::forward<T1> -> int&&, matches g->v1
  //v2 is lvalue,  T2 = int&, std::forward<T2> -> int&, matches g->v2

  // flip(g, v1, v2);  // error
  //v1 is lvalue,  T1 = int&, std::forward<T1> -> int&, mismatches g->v1
  //v2 is lvalue,  T2 = int&, std::forward<T2> -> int&, matches g->v2

  std::cout << "[External]v2 = " << v2 << std::endl;
}

// std::forward preserves the nature of lvalue/rvalue of its corresponding argument

}  // namespace version5

namespace version6 {

template <typename T>
T GetRvalue(T t) {
  return t;
}

template<typename F, typename T1, typename T2>
void flip1(F f, T1&& t1, T2&& t2) {
  f(GetRvalue<T1>(t1), GetRvalue<T2>(t2));
}

template<typename F, typename T1, typename T2>
void flip2(F f, T1&& t1, T2&& t2) {
  f(std::forward<T1>(t1), std::forward<T2>(t2));
}

void g(int&& v1, int& v2) {
  v1 *= 2;
  v2 *= 2;
  std::cout << "[Internal]v1 = " << v1 << ", v2 = " << v2 << std::endl;
}

void test1() {
  int val1 = 8;
  flip1(g, 5, val1);
  std::cout << "[External]val1 = " << val1 << std::endl;

  int val2 = 8;
  flip2(g, 5, val2);
  std::cout << "[External]val2 = " << val2 << std::endl;
}
// 结论证明 val1 and val2值一样，即flip1 and flip2的实现，对于lvalue-reference没有区别

void test2() {
  int val = 1;
  int val1 = 8;
  flip1(g, std::move(val1), val);
  std::cout << "[External]val1 = " << val1 << std::endl;

  int val2 = 8;
  flip2(g, std::move(val2), val);
  std::cout << "[External]val2 = " << val2 << std::endl;
}
// 结论证明val1的值没变，val2的值变了。原因在于T1推到类型为int，但是flip1的第一个参数是int, flip2的第一个参数是int&&，是一个引用，自然能反映对于原变量的修改
// 这也是GetRvalue不如forward的地方
}  // namespace version6

namespace version7 {

template<typename F, typename T1, typename T2>
void flip1(F f, T1&& t1, T2&& t2) {
  f(std::forward<T1>(t1) , std::forward<T2>(t2));
}

void g(int&& v1, int& v2) {
  v1 *= 2;
  v2 *= 2;
  std::cout << "[Internal]v1 = " << v1 << ", v2 = " << v2 << std::endl;
}

void f(int& v1, int&& v2) {
  v1 *= 2;
  v2 *= 2;
  std::cout << "[Internal]v1 = " << v1 << ", v2 = " << v2 << std::endl;
}

void test() {
  int val = 3;
  int& r = val;
  flip1(g, 5, r);
  std::cout << "[External]r = " << r << std::endl;

  flip1(f, r, 5);
  std::cout << "[External]r = " << r << std::endl;
}

}  // namespace version7

namespace version8 {

template<typename T>
T&& myforward(T& param) {
  return static_cast<T&&>(param);
}

//template<typename T>
//T&& myforward(T&& param) {
//  return static_cast<T&&>(param);
//}

template<typename F, typename T1>
void flip(F f, T1&& t1) {
  f(myforward(t1));
  //f(std::forward<T1>(t1) , std::forward<T2>(t2));
}

void g(int& v1) {
  v1 *= 2;
}

void test() {
  int val = 3;
  int& r = val;
  flip(g, r);
}

}  // namespace version8

namespace base {

template <typename T>
T GetRvalue(T t) {
  return t;
}

struct Foo {};

void Bar(int&& val) {
  std::cout << val << std::endl;
}

void test() {
  int&& rr1 = 3;  // legal

  int val = 3;
  // int&& rr2 = val;  // illegal

  int&& rr3 = GetRvalue(val);  // legal

  int&& rr4 = std::move(val);  // legal

  Foo foo;
  //int&& rr5 = std::move(foo);  // illegal type mismatch

  Bar(GetRvalue(rr4));  // illegal
}

}  // namespace base

int main(void) {
  version8::test();
  return 0;
}
