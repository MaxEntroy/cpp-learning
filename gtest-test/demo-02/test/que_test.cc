#include <gtest/gtest.h>

#include "src/que.h"

class QueTest : public ::testing::Test {
 protected:

  void SetUp() override {
    q1_.Enque(1);

    q2_.Enque(2);
    q2_.Enque(3);
  }

  // void TearDown() override {}

  Que<int> q0_;
  Que<int> q1_;
  Que<int> q2_;
};

TEST_F(QueTest, IsEmptyInitially) {
  EXPECT_EQ(q0_.size(), 0);
}

TEST_F(QueTest, EnqueWorks) {
  q0_.Enque(1);
  EXPECT_EQ(q0_.size(), 1);
}

TEST_F(QueTest, DequeWorks) {
  int e = 0;
  int status = q0_.Deque(&e);
  EXPECT_EQ(status, 0);

  status = q1_.Deque(&e);
  EXPECT_EQ(status, 1);
  EXPECT_EQ(q1_.size(), 0);
  EXPECT_EQ(e, 1);

  status = q2_.Deque(&e);
  EXPECT_EQ(status, 1);
  EXPECT_EQ(q2_.size(), 1);
  EXPECT_EQ(e, 2);
}
