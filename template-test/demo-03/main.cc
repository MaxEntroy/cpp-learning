#include <iostream>
#include <string>
#include <sstream>

template<typename T>
std::string debug_rep(const T& t) {
  std::ostringstream oss;
  oss << "[Debug]" << t;
  return oss.str();
}

template<typename T>
std::ostream& print(std::ostream& os, const T& t) {
  return os << t << std::endl;
}

template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args&... rest) {
  os << t << "|";
  return print(os, rest...);
}

template<typename... Args>
std::ostream& err_msg(std::ostream& os, const Args&... rest) {
  return print(os, debug_rep(rest)...);
}

namespace pf {

void f(int&& v1, int& v2) {
  std::cout << "f(int&&, int&) is called, v1 = " << ++v1 << ", v2 = " << v2++ << std::endl;
}

void g(int& v1, int&& v2) {
  std::cout << "g(int&, int&&) is called, v1 = " << v1++ << ", v2 = " << ++v2 << std::endl;
}

void h(std::string& s1, std::string&& s2, char& split) {
  std::cout << "h(string&, string&&, char&) is called, " << s1 << split << s2 << std::endl;
}

template<typename Func, typename... Args>
void wrapper(Func func, Args&&... args) {
  func(std::forward<Args>(args)...);
}

void test() {
  int val = 3;
  int& r{val};
  wrapper(f, 5, r);
  wrapper(g, r, 5);

  std::string s{"perfect"};
  std::string& rs{s};
  char split{','};
  char& rc{split};
  wrapper(h, rs, "forwarding", rc);
}

}  // namespace pf


void test() {
  //print(std::cout, "We will print a lot of vars of difference type" , 32, 3.14, "and a string: hello,world.");
  err_msg(std::cout, "We will print a lot of vars of difference type" , 32, 3.14, "and a string: hello,world.");
}

int main(void) {
  pf::test();
  return 0;
}
