#include <iostream>

int array[1024][1024];

void Loop1() {
  for(int i = 0; i < 1024; i ++) {
    for(int j = 0; j < 1024; j ++) {
      array[i][j] ++;
    }
  }
}

void Loop2() {
  for(int i = 0; i < 1024; i ++)
    for(int j = 0; j < 1024; j ++)
      array[j][i] ++;
}

int main(void) {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      Loop1();
    }
  }
  return 0;
}
