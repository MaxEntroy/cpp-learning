#include "checking_account.h"

#include <iostream>

void CheckingAccount::PrintBalance() {
  std::cout << "Checking account balance: " << GetBalance() << std::endl;
}
