- 模板通用性
  - 我们通过version5的实现发现，在对模板就行实例化的时候，实例化的模板需要和实际调用参数所推到的类型匹配。
  - 这里一开始我的误解是，模板不通用。其实模板是通用的，只是实例化的时候，实参没有和实例化的模板匹配成功

- 通用模板的实现
  - an rvalue reference to a template type parameter (i.e., T&&) preserves the constness and lvalue/rvalue property of its corresponding argument.(大白话：传递左值，形参类型是左值引用；传递右值，形参类型是右值引用)
  - we use forward to pass a function parameter that is defined as an rvalue reference to a template type parameter, which preserves the lvalue/rvalue nature of its given argument(大白话，左值引用变量，还是左值。右值引用变量，变成右值，这是因为右值引用变量，肯定是一个左值)

上面是结论，下面我们仔细讨论下。主要围绕一个问题：右值引用到底是干嘛的？

```cpp
int val = 3;
int& r = val;  // legal
int&& rr = val;  // illegal
int&& rr1 = std::move(val); // legal
```

从这段代码里我们能发现，左值引用和右值引用的主要区别是，一个绑定左值，一个绑定右值。
在绑左值还是绑右值这件事上，类型不起作用。类型的作用是，绑定的右值和引用的绑定的类型，要匹配

```cpp
struct Foo {};
Foo foo;
int&& rr5 = std::move(foo);  
```

这里有一个核心点就是：在绑左值还是绑右值这件事上，类型不起作用。类型只有在校验值类型是否匹配时才起作用。

```cpp
void Bar(int&& val) {
  std::cout << val << std::endl;
}

void Test() {
  int val = 3;
  int&& rr = std::move(val);  // legal

  Bar(rr);  // illegal
}
```

这段代码看上去能编译成功，是因为Bar的参数val的类型是int&&, rr的类型也是int&&，所以类型匹配，可以绑定。但实际编译失败。
因为```int&&```不能当做一个整体的类型去看

```int&& val```的语义是这样：
- 首先，这是一个引用类型，表明对引用的修改即会反映到原值上
- 其次，这个引用类型所绑定的值类型是整型，表明该引用只能绑整型
- 最后，这个引用只能绑右值

**不能用形式上的类型去看，对于别的类型可以，但是对于T&&类型不行**。

对于```rr```来说，它本身是一个lvalue，所以函数调用时，第一步判断就失败。因为```val```只能绑定右值
这就是上面为什么强调**在绑左值还是绑右值这件事上，类型不起作用**，本质是想强调需要分两步看这个类型声明

想让上面的调用成功，我们的处理办法也很简单。在左值的基础上，产生一个对应的右值。写一个产生临时变量的函数即可
```cpp
template<typename T>
T GetRvalue(T t) {
  return t;
}

void Bar(int&& val) {
  std::cout << val << std::endl;
}

void Test() {
  int val = 3;
  int&& rr = GetRvalue(val);  

  Bar(GetRvalue(rr)); 
}
```

那既然这个函数可以，为什么我们还需要std::forward，我们看下面的例子

```cpp
template <typename T>
T GetRvalue(T t) {
  return t;
}

template<typename F, typename T1, typename T2>
void flip1(F f, T1&& t1, T2&& t2) {
  f(GetRvalue<T1>(t1), GetRvalue<T2>(t2));
}

template<typename F, typename T1, typename T2>
void flip2(F f, T1&& t1, T2&& t2) {
  f(std::forward<T1>(t1), std::forward<T2>(t2));
}

void g(int&& v1, int& v2) {
  v1 *= 2;
  v2 *= 2;
  std::cout << "[Internal]v1 = " << v1 << ", v2 = " << v2 << std::endl;
}

void test1() {
  int val1 = 8;
  flip1(g, 5, val1);
  std::cout << "[External]val1 = " << val1 << std::endl;

  int val2 = 8;
  flip2(g, 5, val2);
  std::cout << "[External]val2 = " << val2 << std::endl;
}
// 结论证明 val1 and val2值一样，即flip1 and flip2的实现，对于lvalue-reference没有区别

void test2() {
  int val = 1;
  int val1 = 8;
  flip1(g, std::move(val1), val);
  std::cout << "[External]val1 = " << val1 << std::endl;

  int val2 = 8;
  flip2(g, std::move(val2), val);
  std::cout << "[External]val2 = " << val2 << std::endl;
}
// 结论证明val1的值没变，val2的值变了。原因在于T1推到类型为int，但是flip1的第一个参数是int, flip2的第一个参数是int&&，是一个引用，自然能反映对于原变量的修改
// 这也是GetRvalue不如forward的地方
```

很明显，std::forward<T> return T&&，本质是返回了一个引用类型，引用类型表明：对于该引用的修改会反映到关联值上，但是GetRvalue<T> return T，返回的是值类型，对于该值的修改，不会反映到原变量上。

这里多说一点，std::move和std::forward的区别在于，后者有reference collapsing，而前者不行。