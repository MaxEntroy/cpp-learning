#include <unistd.h>

#include <gflags/gflags.h>
#include <glog/logging.h>

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  while(1) {
    LOG(INFO) << "hello, world" << std::endl;
    sleep(1);
  }

  return 0;
}
