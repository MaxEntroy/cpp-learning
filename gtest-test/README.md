## demo-01

第一个demo给出一些基本的经验

q:测试架构在使用时需要关注什么?
>1.测试结构(即测试代码的程序组织结构)
2.断言方法

q:gtest测试结构是如何组织的?
>第一个demo学到的主要是利用宏，来组织一个基本测例

```cpp
// 测试单元
TEST(TestSuiteName, TestName) {
  ... test body ...
}

// 触发测例
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```

q:写测例应该从那些方面考虑?
>类似刷题的感觉:
1.基本逻辑
2.异常逻辑
3.边界逻辑
其实，从更一般的角度来说，保证被测函数的每一个执行逻辑，都可以被测试到

```cpp
int add(int left, int right) {
  if(left < 0 || right < 0) {
    std::cerr << "Can only add positive numbers, received " << left << " and "
      << right << std::endl;
    return -1;
  }

  if(!left || !right)
    return 0;

  return left + right;
}

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
```

参考<br>
[gtest快速上手](https://segmentfault.com/a/1190000002454946)

## demo-02

本小节，对于gtest进行系统的学习

Basic Concepts
- When using googletest, you start by writing assertions, which are statements that check whether a condition is true.An assertion's result can be:
  - success
  - nonfatal failure
  - fatal failure
- Tests use assertions to verify the tested code's behavior.
- A test suite contains one or many tests
  - You should group your tests into test suites
  - When multiple tests in a test suite need to share common objects and subroutines, you can put them into a test fixture class
- A test program can contain multiple test suites.


Assertions
- ASSERT_* versions generate fatal failures when they fail, and abort the current function
- EXPECT_* versions generate nonfatal failures, which don't abort the current function.
- Since a failed ASSERT_* returns from the current function immediately, possibly skipping clean-up code that comes after it, it may cause a space leak. 
- Anything that can be streamed to an ostream can be streamed to an assertion macro

Test Fixtures: Using the Same Data Configuration for Multiple Tests {#same-data-multiple-tests}
- googletest does not reuse the same test fixture for multiple tests
- Any changes one test makes to the fixture do not affect other tests.
虽说，Test Fixtures的语义是提供不同测例之间的共享数据，但是本质上来说，只是为测例提供一些preconditions，各个测例之间还是相互不影响。