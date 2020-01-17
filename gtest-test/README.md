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