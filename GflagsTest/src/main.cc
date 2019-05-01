#include <iostream>

#include <gflags/gflags.h>

DEFINE_string(host, "127.0.0.1", "the server host");
DEFINE_int32(port, 6035, "the server port");

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    std::cout << "Server host: " << FLAGS_host << std::endl
        << "Server port: " << FLAGS_port << std::endl;

    return 0;
}
