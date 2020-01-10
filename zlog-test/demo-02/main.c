#include "log.h"

void test_zlog() {
  pzlog c = LOG_INIT("test_hello.conf", "my_cat");

  LOG(c, INFO, "hello, zlog");

  LOG_FINI();
}

int main(void) {
  test_zlog();
  return 0;
}
