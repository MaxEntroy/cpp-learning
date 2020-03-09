#include <gtest/gtest.h>

#include "common/cal.h"

TEST(AddTest, HandlePositive) {
  EXPECT_EQ(add(1,2), 3);
}

TEST(AddTest, HandleZero) {
  EXPECT_EQ(add(0, 1), 0);
  EXPECT_EQ(add(1, 0), 0);
  EXPECT_EQ(add(0, 0), 0);
}

TEST(AddTest, HandleNegative) {
  EXPECT_EQ(add(-2, 3), -1);
  EXPECT_EQ(add(3, -3), -1);
  EXPECT_EQ(add(-1, -3), -1);
  EXPECT_EQ(add(-1, -0), -1);
}
