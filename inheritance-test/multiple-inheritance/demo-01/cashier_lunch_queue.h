#ifndef CASHIER_LUNCH_QUEUE_H_
#define CASHIER_LUNCH_QUEUE_H_

#include <iostream>

#include "cashier_queue.h"
#include "lunch_queue.h"

class CashierLunchQueue :
  public CashierQueue, public LunchQueue {
 public:
  CashierLunchQueue() : CashierQueue(), LunchQueue() {
    std::cout << "CashierLunchQueue called." << std::endl;
  }
};

#endif
