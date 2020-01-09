#include <stdio.h>
#include <zlog/zlog.h>

int main(void) {

  int rc;
  zlog_category_t *c;

  rc = zlog_init("test_hello.conf");

  if (rc) {

  printf("init failed\n");
  return -1;

  }

  c = zlog_get_category("my_cat");

  if (!c) {

  printf("get cat fail\n");

  zlog_fini();
  return -2;

  }

  zlog_info(c, "hello, zlog");

  zlog_fini();

  return 0;

}
