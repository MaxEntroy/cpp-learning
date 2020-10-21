#ifndef BIZ_H_
#define BIZ_H_

#include <string>

#include "role/user.h"
#include "mock_user.h"

class Biz {
 public:
  Biz() : user_(nullptr) {}

  Biz(const Biz&) = delete;
  Biz& operator=(const Biz&) = delete;

  void SetUser(User* user) { user_ = user; }
  bool Pay(const std::string& user_name, const std::string& pwd, int money);

 private:
  // user_ is not responsible for resource management.
  User* user_;
};  // class Biz

#endif  // BIZ_H_
