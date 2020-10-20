#ifndef BIZ_H_
#define BIZ_H_

#include <iostream>
#include <string>

#include "role/user.h"

namespace gt {

template<class UserType>
class Biz {
 public:
  Biz() : user_(nullptr) {}

  Biz(const Biz&) = delete;
  Biz& operator=(const Biz&) = delete;

  void SetUser(UserType* user) { user_ = user; }
  bool Pay(const std::string& user_name, const std::string& pwd, int money);

 private:
  // user_ is not responsible for resource management.
  UserType* user_;
};  // class Biz

template<class UserType>
bool Biz<UserType>::Pay(const std::string& user_name, const std::string& pwd, int money) {
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

}  // namespace gt

#endif  // BIZ_H_
