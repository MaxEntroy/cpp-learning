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

q:Text Fixtures到底有什么用？
>我理解，还是对有状态函数的测试，其中的状态可以通过上下文进行测试。

最典型的例子是对于类的测试，显然类对象是有状态的。对于状态的设置，可以通过上下文的一些函数来进行控制
```cpp
#ifndef QUE_H_
#define QUE_H_

#include <stdio.h>

#include <queue>

template<class T>
class Que {
 public:
  Que() {}

  // Inserts a new element at the end of the queue.
  void Enque(const T& e);

  // Remove the "oldest" element from the queue and return it.
  // Return 0 if the queue is empty. Otherwise, return 1.
  int Deque(T* e);

  // Return the size of the queue.
  size_t size() const;

 private:
  std::queue<T> q_;

};

template<class T>
void Que<T>::Enque(const T& e) {
  q_.push(e);
}

template<class T>
int Que<T>::Deque(T* e) {
  if(q_.empty())
    return 0;

  *e = q_.front();
  q_.pop();

  return 1;
}

template<class T>
size_t Que<T>::size() const {
  return q_.size();
}

#endif
```

一些具体的细节，看gtest的文档即可。我说下测试成员函数和普通函数的一些细节：
- 非成员函数，多个测例给到不同的输入，测试不同program path
- 成员函数，多个测例测试不同的成员函数，测例内部给到不同的数据，测试不同的program path.
- 对于program path的测试，可以他通过多组断言来验证，这个能力要有。参考对于Deque的测试

```cpp
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

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
```

最后，```main```函数不写也是可以的，需要```-lgtest_main```