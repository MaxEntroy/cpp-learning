#ifndef SAVING_ACCOUNT_H_
#define SAVING_ACCOUNT_H_

#include "account.h"

class SavingAccount : public Account {
 public:
  SavingAccount() : Account() {}
  explicit SavingAccount(int balance) : Account(balance) {}

  virtual void PrintBalance();
};

#endif
