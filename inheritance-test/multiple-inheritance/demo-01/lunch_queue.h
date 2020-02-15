#ifndef LUNCH_QUEUE_H_
#define LUNCH_QUEUE_H_

#include <iostream>

#include "queue.h"

class LunchQueue : public Queue {
 public:
  LunchQueue() : Queue() {
    std::cout << "LunchQueue called." << std::endl;
  }
};

#endif
