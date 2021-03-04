#include <iostream>
#include <mutex>
#include <thread>

int foo = 0;
std::once_flag onceFlag;  // global state

void FooInit() { ++foo; }

void FooInitOnce() {
  std::call_once(onceFlag, &FooInit);
}

void Test01() {
  std::thread t1(FooInit);
  t1.join();

  std::thread t2(FooInit);
  t2.join();

  std::cout << "foo = " << foo << std::endl;
}

void Test02() {
  std::thread t1(FooInitOnce);
  t1.join();

  std::thread t2(FooInitOnce);
  t2.join();

  std::cout << "foo = " << foo << std::endl;
}

int main(void) {
  Test01();
  //Test02();
  return 0;
}
