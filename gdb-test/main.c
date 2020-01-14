#include <stdio.h>

void say_hello();

int main(void) {

  say_hello();

  return 0;
}

void say_hello() {
  printf("say_hello is called.\n");

  printf("hello, world.\n");
}
