#include "biz.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::_;

class BizTest : public ::testing::Test {
 protected:
  Biz foo;
  User user;
};

TEST_F(BizTest, HandleInvlidUser) {
  foo.SetUser(&user);
  EXPECT_FALSE(foo.Pay("admin", "123", 100));
}

TEST_F(BizTest, HandleOfflineWithLoginFailed) {
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
  EXPECT_CALL(user, Online())
    .Times(1)
    .WillOnce(Return(true));
  EXPECT_CALL(user, Pay(_))
    .Times(1)
    .WillOnce(Return(false));

  foo.SetUser(&user);
  EXPECT_FALSE(foo.Pay("admin", "123", 100));
}
