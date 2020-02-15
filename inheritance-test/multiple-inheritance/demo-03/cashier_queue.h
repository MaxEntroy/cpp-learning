#ifndef CASHIER_QUEUE_H_
#define CASHIER_QUEUE_H_

#include <iostream>

#include "queue.h"

class CashierQueue : virtual public Queue {
 public:
  CashierQueue(int cashier_cnt, int cnt) :
    Queue(cnt), cashier_que_cnt_(cashier_cnt) {
    std::cout << "CashierQueue called. cashier_que_cnt = " << cashier_que_cnt_ << std::endl;
  }

 private:
  int cashier_que_cnt_;
};

#endif
