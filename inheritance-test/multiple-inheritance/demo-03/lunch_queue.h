#ifndef LUNCH_QUEUE_H_
#define LUNCH_QUEUE_H_

#include <iostream>

#include "queue.h"

class LunchQueue : virtual public Queue {
 public:
  LunchQueue(int lunch_cnt, int cnt) :
    Queue(cnt), lunch_que_cnt_(lunch_cnt){
    std::cout << "LunchQueue called. lunch_que_cnt = " << lunch_que_cnt_ << std::endl;
  }

 private:
  int lunch_que_cnt_;
};

#endif
