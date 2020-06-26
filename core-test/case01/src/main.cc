#include <iostream>
#include <gflags/gflags.h>

DEFINE_int32(lhs, 1, "");
DEFINE_int32(rhs, 1, "");

int mydiv(int lhs, int rhs) {
  return lhs / rhs;
}

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  mydiv(FLAGS_lhs, FLAGS_rhs);
  return 0;
}
