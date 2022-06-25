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
  os << t << ",";
  return print(os, rest...);
}

template<typename... Args>
std::ostream& err_msg(std::ostream& os, const Args&... rest) {
  return print(os, debug_rep(rest)...);
}

void test() {
  //print(std::cout, "We will print a lot of vars of difference type" , 32, 3.14, "and a string: hello,world.");
  err_msg(std::cout, "We will print a lot of vars of difference type" , 32, 3.14, "and a string: hello,world.");
}

int main(void) {
  test();
  return 0;
}
