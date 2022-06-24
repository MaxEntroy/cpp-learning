#include <iostream>

template<typename T>
std::ostream& print(std::ostream& os, const T& t) {
  return os << t << std::endl;
}

template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args&... rest) {
  os << t << ",";
  return print(os, rest...);
}

int main(void) {
  print(std::cout, "We will print a lot of vars of difference type" , 32, 3.14, "and a string: hello,world.");
  return 0;
}
