#include "biz.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::_;

class MockUser : public gt::User {
 public:
  MOCK_METHOD2(Login, bool(const std::string&, const std::string&));
  MOCK_METHOD1(Pay, bool(int));
  MOCK_METHOD0(Online, bool());
};

class BizTest : public ::testing::Test {
 protected:
  gt::Biz foo;
};

TEST_F(BizTest, HandleInvlidUser) {
  EXPECT_FALSE(foo.Pay("admin", "123", 100));
}

TEST_F(BizTest, HandleOfflineWithLoginFailed) {
  MockUser user;
  EXPECT_CALL(user, Online())
    .Times(1)
    .WillOnce(Return(false));
  EXPECT_CALL(user, Login(_, _))
    .Times(1)
    .WillOnce(Return(false));

  foo.SetUser(&user);
  EXPECT_FALSE(foo.Pay("admin", "123", 100));
}

TEST_F(BizTest, HandleOfflineWithLoginSuccessfullyAndPayFailed) {
  MockUser user;
  EXPECT_CALL(user, Online())
    .Times(1)
    .WillOnce(Return(false));
  EXPECT_CALL(user, Login(_, _))
    .Times(1)
    .WillOnce(Return(true));
  EXPECT_CALL(user, Pay(_))
    .Times(1)
    .WillOnce(Return(false));

  foo.SetUser(&user);
  EXPECT_FALSE(foo.Pay("admin", "123", 100));
}

TEST_F(BizTest, HandleOfflineWithLoginSuccessfullyAndPaySuccessfully) {
  MockUser user;
  EXPECT_CALL(user, Online())
    .Times(1)
    .WillOnce(Return(false));
  EXPECT_CALL(user, Login(_, _))
    .Times(1)
    .WillOnce(Return(true));
  EXPECT_CALL(user, Pay(_))
    .Times(1)
    .WillOnce(Return(true));

  foo.SetUser(&user);
  EXPECT_TRUE(foo.Pay("admin", "123", 100));
}

TEST_F(BizTest, HandleOnlineWithPaySuccessfully) {
  MockUser user;
  EXPECT_CALL(user, Online())
    .Times(1)
    .WillOnce(Return(true));
  EXPECT_CALL(user, Pay(_))
    .Times(1)
    .WillOnce(Return(true));

  foo.SetUser(&user);
  EXPECT_TRUE(foo.Pay("admin", "123", 100));
}

TEST_F(BizTest, HandleOnlineWithPayFailed) {
  MockUser user;
  EXPECT_CALL(user, Online())
    .Times(1)
    .WillOnce(Return(true));
  EXPECT_CALL(user, Pay(_))
    .Times(1)
    .WillOnce(Return(false));

  foo.SetUser(&user);
  EXPECT_FALSE(foo.Pay("admin", "123", 100));

}
