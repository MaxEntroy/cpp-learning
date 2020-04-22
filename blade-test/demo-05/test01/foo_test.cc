#include <gtest/gtest.h>
#include "foo.h"

using namespace bt;

class FooTest : public ::testing::Test {
 protected:
  Foo foo;
};

TEST_F(FooTest, HandleGetX) {
  EXPECT_EQ(foo.GetX(), 0);
}
