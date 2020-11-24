#include <iostream>
#include <type_traits>

template<typename ValueType>
void foo(ValueType val) {
  if (std::is_same<ValueType, int>::value) {
    std::cout << "int type" << std::endl;
  } else if (std::is_same<ValueType, int&>::value) {
    std::cout << "int& type" << std::endl;
  } else if (std::is_same<ValueType, const int&>::value) {
    std::cout << "const int& type" << std::endl;
  } else if (std::is_same<ValueType, int*>::value) {
    std::cout << "int* type" << std::endl;
  } else if (std::is_same<ValueType, const int*>::value) {
    std::cout << "const int* type" << std::endl;
  } else {
    std::cout << "other type" << std::endl;
  }
}

template<typename ValueType>
void foo_01(ValueType val) {
  if (std::is_same<ValueType, int>::value) {
    std::cout << "int type" << std::endl;
  } else {
    std::cout << "other type" << std::endl;
  }
}

template<class T>
using decay_t = typename std::decay<T>::type;

template<typename ValueType>
void foo_01_decay(ValueType val) {
  if (std::is_same<decay_t<ValueType>, int>::value) {
    std::cout << "int type" << std::endl;
  } else {
    std::cout << "other type" << std::endl;
  }
}

void test01() {
  int val = 13;
  int& val_ref = val;
  const int& const_val_ref = val;
  int* val_ptr = &val;
  const int* const_val_ptr = &val;

  foo(val);
  foo(val_ref);
  foo(const_val_ref);
  foo(val_ptr);
  foo(const_val_ptr);
}

void test02() {
  int val = 13;
  int& val_ref = val;
  const int& const_val_ref = val;
  int* val_ptr = &val;
  const int* const_val_ptr = &val;

  foo<int>(val);
  foo<int&>(val_ref);
  foo<const int&>(const_val_ref);
  foo<int*>(val_ptr);
  foo<const int*>(const_val_ptr);
}

void test03() {
  int val = 13;
  int& val_ref = val;
  const int& const_val_ref = val;
  int* val_ptr = &val;
  const int* const_val_ptr = &val;

  foo_01<int>(val);
  foo_01<int&>(val_ref);
  foo_01<const int&>(const_val_ref);
  foo_01<int*>(val_ptr);
  foo_01<const int*>(const_val_ptr);
}

void test04() {
  int val = 13;
  int& val_ref = val;
  const int& const_val_ref = val;
  int* val_ptr = &val;
  const int* const_val_ptr = &val;

  foo_01_decay<int>(val);
  foo_01_decay<int&>(val_ref);
  foo_01_decay<const int&>(const_val_ref);
  foo_01<int*>(val_ptr);
  foo_01<const int*>(const_val_ptr);
}

int main(void) {
  test04();
  return 0;
}
