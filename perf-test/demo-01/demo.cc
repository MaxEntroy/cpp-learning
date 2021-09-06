#include <iostream>

#include <gperftools/profiler.h>

int array[1024][1024];

void Loop1() {
  for(int i = 0; i < 1024; i ++) {
    for(int j = 0; j < 1024; j ++) {
      array[i][j] ++;
    }
  }
}

int main(void) {
  ProfilerStart("cpu.prof");
  for (int i = 0; i < 1024; ++i) {
    for (int j = 0; j < 1024; ++j) {
      Loop1();
    }
  }
  ProfilerStop();
  // pprof  ./demo cpu.prof --pdf > cpu.prof.pdf
  return 0;
}
