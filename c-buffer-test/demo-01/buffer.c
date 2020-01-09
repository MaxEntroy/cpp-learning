#include <stdio.h>
#include <unistd.h>

#define TRUE 1

int main(void) {
  while(TRUE) {
    printf("buffer test.");
    sleep(1);
  }
  return 0;
}
