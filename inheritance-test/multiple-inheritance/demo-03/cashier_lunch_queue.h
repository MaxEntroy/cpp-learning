#ifndef CASHIER_LUNCH_QUEUE_H_
#define CASHIER_LUNCH_QUEUE_H_

#include <iostream>

#include "cashier_queue.h"
#include "lunch_queue.h"

class CashierLunchQueue :
  public CashierQueue, public LunchQueue {
 public:
  CashierLunchQueue(int cashier_lunch_cnt,
                    int cashier_cnt,
                    int lunch_cnt,
                    int cnt) :
    Queue(cnt),
    CashierQueue(cashier_cnt, cnt),
    LunchQueue(lunch_cnt, cnt),
    cashier_lunch_que_cnt_(cashier_lunch_cnt){
    std::cout << "CashierLunchQueue called. cashier_lunch_que_cnt = " << cashier_lunch_que_cnt_ << std::endl;
  }

 private:
  int cashier_lunch_que_cnt_;
};

#endif
