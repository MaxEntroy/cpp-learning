#include <iostream>

int mydiv(int lhs, int rhs) {
  return lhs / rhs;
}

int main(void) {
  int a = 1, b = 1;
  while(std::cin >> a >> b) {
    std::cout << mydiv(a, b) << std::endl;
  }

  return 0;
}
