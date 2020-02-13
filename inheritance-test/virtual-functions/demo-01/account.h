#ifndef ACCOUNT_H_
#define ACCOUNT_H_

class Account {
 public:
  Account() {}
  explicit Account(int balance) : balance_(balance) {}

  int GetBalance() const {return balance_;}
  virtual void PrintBalance();

 private:
  int balance_;
};

#endif
