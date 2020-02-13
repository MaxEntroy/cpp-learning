#ifndef CHECKING_ACCOUNT_H_
#define CHECKING_ACCOUNT_H_

#include "account.h"

class CheckingAccount : public Account {
 public:
  CheckingAccount() : Account() {}
  explicit CheckingAccount(int balance) : Account(balance) {}

  virtual void PrintBalance();
};

#endif
