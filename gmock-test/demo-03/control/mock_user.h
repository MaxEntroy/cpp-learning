#ifndef MOCK_USER_H_
#define MOCK_USER_H_

#ifdef USER_TEST

#include <gmock/gmock.h>

#define User MockUser

class MockUser {
 public:
  MOCK_METHOD2(Login, bool(const std::string&, const std::string&));
  MOCK_METHOD1(Pay, bool(int));
  MOCK_METHOD0(Online, bool());
};  // MockUser

#endif  // USER_TEST

#endif // MOCK_USER_H_
