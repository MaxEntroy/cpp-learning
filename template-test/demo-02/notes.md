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
- val只能绑右值
- 绑定值的类型是int

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

那既然这个函数可以，为什么我们还需要std::move/std::forward，我们看move的实现。

```cpp
// remove_reference is covered in § 16.2.3 (p. 684)
template <typename T>
typename remove_reference<T>::type&& move(T&& t)
{
  // static_cast covered in § 4.11.3 (p. 163)
  return static_cast<typename remove_reference<T>::type&&>(t);
```

先来回答一个基本问题，为什么Bar的参数```int&& val```不可以接受rr，而move的参数```T&& t```可以接受rr。
因为后者是universal reference，而前者不是。

我们再来看，move到底比GetRvalue好在哪？后者没有reference collapsing的能力，后者不管任何情况，t的类型就是T。但是前者可能是T&，也可能是T&&，即前者保留了一个引用变量的左右值属性，也即保留了一个引用变量绑定值的属性(lvalue or rvalue).

最终，我们把话题说回lvalue/rvalue，rvalue存在的意义只有一个，即这个变量的值可以被窃取。
