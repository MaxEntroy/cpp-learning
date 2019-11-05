q:std::function有什么用？
>Class template std::function is a general-purpose polymorphic function wrapper.

q:如何理解？
>我理解是对于函数作为一等公民的支持，cpp本身不支持，所以通过一个function wrapper来实现这种语义。

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