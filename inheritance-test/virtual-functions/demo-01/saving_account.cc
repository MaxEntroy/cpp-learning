#include "saving_account.h"

#include <iostream>

void SavingAccount::PrintBalance() {
  std::cout << "Savings account balance: " << GetBalance() << std::endl;
}
