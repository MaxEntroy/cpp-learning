#include "src/cal.h"

#include <gtest/gtest.h>

TEST(AddTest, HandlePositive) {
  EXPECT_EQ(add(1,2), 3);
}

TEST(AddTest, HandleZero) {
  EXPECT_EQ(add(0,3), 0);
  EXPECT_EQ(add(3,0), 0);
  EXPECT_EQ(add(0,0), 0);
}

TEST(AddTest, HandleNegative) {
  EXPECT_EQ(add(-1,1), -1);
  EXPECT_EQ(add(1,-1), -1);
  EXPECT_EQ(add(-1,-1), -1);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
