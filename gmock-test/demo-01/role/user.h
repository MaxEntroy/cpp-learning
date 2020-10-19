#ifndef USER_H_
#define USER_H_

#include <string>

namespace gt {

class User {
 public:
  User() = default;

  User(const User&) = delete;
  User& operator=(const User&) = delete;

  virtual ~User() = default;

  virtual bool Login(const std::string& user_name, const std::string& pwd) = 0;
  virtual bool Pay(int money) = 0;
  virtual bool Online() = 0;
};  // class User

}  // namespace gt

#endif  // namespace USER_H_
