#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>

class Queue {
 public:
  Queue(int cnt) : que_cnt_(cnt) {
    std::cout << "Queue constructor called. que_cnt = " << que_cnt_ << std::endl;
  }

 private:
  int que_cnt_;
};

#endif
