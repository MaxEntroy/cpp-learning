## default-delete-test

### default

**C.80: Use =default if you have to be explicit about using the default semantics**

1. 这条规则是说，当我们需要定义默认语义的对象管理函数时，使用default来声明，而不是自己写
2. 具体对象管理函数有
2.1. contructor semantics
2.2. destructor semantics
2.3. copy semantics
2.4. assignment semantics
2.5. move semantics

q:这么做的原因是?
>Writing out the bodies of the copy and move operations is verbose, tedious, and error-prone. A compiler does it better.

我们来看一个例子，下面的类，由于定义了destructor，根据rule of five，需要定义其余的4个函数。
但是编译器默认生成的可以满足要求(即没有自己实现的必要)，所以，没有必要现实定义其余4个对象管理函数。

- best practice

```cpp
class Tracer {
    string message;
public:
    Tracer(const string& m) : message{m} { cerr << "entering " << message << '\n'; }
    ~Tracer() { cerr << "exiting " << message << '\n'; }

    Tracer(const Tracer&) = default;
    Tracer& operator=(const Tracer&) = default;
    Tracer(Tracer&&) = default;
    Tracer& operator=(Tracer&&) = default;
};
```

- bad practice
```cpp
class Tracer2 {
    string message;
public:
    Tracer2(const string& m) : message{m} { cerr << "entering " << message << '\n'; }
    ~Tracer2() { cerr << "exiting " << message << '\n'; }

    Tracer2(const Tracer2& a) : message{a.message} {}
    Tracer2& operator=(const Tracer2& a) { message = a.message; return *this; }
    Tracer2(Tracer2&& a) :message{a.message} {}
    Tracer2& operator=(Tracer2&& a) { message = a.message; return *this; }
};
```

### delete

**C.81: Use =delete when you want to disable default behavior (without wanting an alternative)**

1. 当对象管理函数的语义禁止时，采用delete来声明。最后括号里的是说，如果你觉得默认语义无法满足，需要自己实现一个版本，那不能这么做。
2. The elimination of a default operation is (should be) based on the desired semantics of the class.

作者举了一个unique_ptr的例子

```cpp
template <class T, class D = default_delete<T>> class unique_ptr {
public:
    // ...
    constexpr unique_ptr() noexcept;
    explicit unique_ptr(pointer p) noexcept;
    // ...
    unique_ptr(unique_ptr&& u) noexcept;   // move constructor
    // ...
    unique_ptr(const unique_ptr&) = delete; // disable copy from lvalue
    // ...
};
```

参考
[C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-eqdefault)
