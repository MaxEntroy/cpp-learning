#ifndef CASHIER_QUEUE_H_
#define CASHIER_QUEUE_H_

#include <iostream>

#include "queue.h"

class CashierQueue : public Queue {
 public:
  CashierQueue() : Queue() {
    std::cout << "CashierQueue called." << std::endl;
  }
};

#endif
