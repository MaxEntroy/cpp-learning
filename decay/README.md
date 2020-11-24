## 实践

### decay

- demo-01

首先给出一段代码，对于模板类型信息进行获取

```cpp
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
```

我们先来看第一段代码和结果
```cpp
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
/*
int type
int type
int type
int* type
const int* type
*/
```
从上面的结论中我们可以发现，std::is_same具有如下特点：
当直接通过实参获取类型时
- T& 获取为T
- const T& 获取为T
- T*/const T*获取正常

再来看一段代码
```cpp
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
```

使用泛型时显示指定类型，不进行类型推到。则没有问题。

我们更换对于ValueType的判断代码，此时运行test02相同的client code
```cpp
template<typename ValueType>
void foo_01(ValueType val) {
  if (std::is_same<ValueType, int>::value) {
    std::cout << "int type" << std::endl;
  } else {
    std::cout << "other type" << std::endl;
  }
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
/*
int type
other type
other type
other type
other type
*/
```

如上所言，调用模板函数时，显示指定类型，不进行推到。则ValueType可以获取到原有的类型。
但是，现在我们想忽略，const T&, T&, T这3者之间的区别。以为我们在进行参数传递时，经常会避免对象拷贝采用以上两种类型，我们希望他么你的推到类型一致，是否有办法可解决？

还是先看代码
```cpp
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
/*
int type
int type
int type
other type
other type
*/
```

很明显，通过decay，将类型ValueType的reference和const属性全部去掉了，从而保持了类型的一致。但是指针的特性无法去除。
这里的decay_t可以理解为一个类型萃取器，对模板类型进行萃取，并同时修改类型的限制。