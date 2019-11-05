q:std::function有什么用？
>Class template std::function is a general-purpose polymorphic function wrapper.

q:如何理解？
>我理解是对于函数作为一等公民的支持，cpp本身不支持，所以通过一个function wrapper来实现这种语义。

q:函数指针类型不安全？
还有很重要一点在于，std::function是类型安全的，但是诸如函数指针这样的可调用对象，并不是类型安全的。
对于函数指针，定义int(*)(int, int)，如果我们实际传递int(*)(int)，也是可以的，fn不过是一个指向函数的指针，我们无法判断这个指针实际指向什么，像参数和返回类型等无从知晓。

```cpp
#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

// 编译通过 正常执行 但逻辑错误
void test_func_pointer() {

    typedef int(*func1)(int);
    func1 f1 = (func1)add;
    int ret = f1(20);
    std::cout << "ret1 = " << ret << std::endl;

    typedef int(*func2)(int, int, int);
    func2 f2 = (func2)add;
    int ret2 = f2(20, 30, 10);
    std::cout << "ret2 = " << ret2 << std::endl;
}

// 编译不通过 无法执行
void test_function_object() {

    typedef std::function<int(int)> func1;
    func1 f1 = (func1)add;
    int ret = f1(20);
    std::cout << "ret1 = " << ret << std::endl;

    typedef std::function<int(int, int, int)> func2;
    func2 f2 = (func2)add;
    int ret2 = f2(20, 30, 10);
    std::cout << "ret2 = " << ret2 << std::endl;
}

int main(int argc, const char * argv[])
{
    test_func_pointer();
    test_function_object();
    return 0;
}
/*
引入std::function，可以获得确切的类型信息，类型不匹配无法转换。
但是函数指针不具备这个能力。
ps:为什么int,float,double类型不一致，也可以强转。因为int,float,double之间的本质类型都是"number"，区别在于精度。
但是，函数标签不一样，根本就不是同一种类型
*/
```


q:std::find有什么用？
>The function template bind generates a forwarding call wrapper for f. 
Calling this wrapper is equivalent to invoking f with some of its arguments bound to args.

q:如何理解？
>将可调用对象和其参数进行绑定，生成一个新的可调用对象。

具体作用如下：
- 将可调用对象和其参数绑定成一个functor
- 只绑定部分参数，减少可调用对象传入的参数。

参考
[C++11 中的std::function和std::bind](https://www.jianshu.com/p/f191e88dcc80)
[std::function](https://en.cppreference.com/w/cpp/utility/functional/function)
[C/C++函数指针参数不匹配问题](https://blog.csdn.net/oktears/article/details/39452341)