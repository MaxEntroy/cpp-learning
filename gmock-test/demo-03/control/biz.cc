#include "biz.h"

#include <iostream>

bool Biz::Pay(const std::string& user_name, const std::string& pwd, int money) {
  if (!user_) {
    std::cerr << "Invalid user.";
    return false;
  }

  if (!user_->Online()) {
    if (!user_->Login(user_name, pwd)) {
      std::cerr << "Login failed.";
      return false;
    }
  }

  if (!user_->Pay(money)) {
    std::cerr << "Pay failed.";
    return false;
  }

  return true;
}
