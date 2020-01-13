#include <stdio.h>
#include <stdarg.h>

void myprintf(const char* format, ...) {
  printf("myprintf called.\n");
  printf(format, __VA_ARGS__);
}

//#define MYPRINT(format, ...) \
//  printf("MYPINT called.\n");           \
//  printf(format, ##__VA_ARGS__);

int main(void) {
  //myprintf("hello, word: %s\n", "var_list");
  MYPRINT("hello, world: %s\n", "var_list");
  return 0;
}

