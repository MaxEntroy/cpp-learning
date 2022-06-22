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

  // flip(g, 5, v2);
  //5 is rvalue,   T1 = int,  std::forward<T1> -> int&&, matches g->v1
  //v2 is lvalue,  T2 = int&, std::forward<T2> -> int&, matches g->v2

  // flip(g, v1, v2);  // error
  //v1 is lvalue,  T1 = int&, std::forward<T1> -> int&, mismatches g->v1
  //v2 is lvalue,  T2 = int&, std::forward<T2> -> int&, matches g->v2

  std::cout << "[External]v2 = " << v2 << std::endl;
}

// std::forward preserves the nature of lvalue/rvalue of its corresponding argument

}  // namespace version5

int main(void) {
  version5::test();
  return 0;
}
