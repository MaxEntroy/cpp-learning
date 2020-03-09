#include <iostream>

#include <gflags/gflags.h>

// #include "task.h"
#include "proto/cal_req.pb.h"
#include "proto/cal_res.pb.h"

DEFINE_int32(left, 0, "left opnd");
DEFINE_int32(right, 0, "right opnd");

int main(int argc, char* argv[]) {
  if(argc != 3) {
    std::cerr << "Usage: ./main opnd1 opnd2.\n";
    return 1;
  }

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  cal::Request req;
  cal::Response res;
  // DoRequest(&req, FLAGS_left, FLAGS_right);
  // DoTask(req, &res);
  // DoResponse(res);

  return 0;
}
