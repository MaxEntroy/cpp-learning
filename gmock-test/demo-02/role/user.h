#ifndef USER_H_
#define USER_H_

#include <string>

namespace gt {

class User {
 public:
  User() = default;

  User(const User&) = delete;
  User& operator=(const User&) = delete;

  bool Login(const std::string& user_name, const std::string& pwd);
  bool Pay(int money);
  bool Online();
};  // class User

}  // namespace gt

#endif  // namespace USER_H_
