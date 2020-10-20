本小节在demo-01的基础上，给出non-virtual functions的mock方法，主要参照[cook-book](https://github.com/google/googletest/blob/master/googlemock/docs/cook_book.md)的方法进行

首先我们先回顾virtual functions的测试方法：
1. Define MockFoo class which is derived from Foo class.
2. Define mock method which override virtual functions in base class.
3. Setting Expectations.

- 这里，由于派生类和基类存在inheritance关系，并且mock method 对虚函数进行了override.
- 使用时，基类的指针指向派生类对象。此时在业务代码中基类指针调用对应虚函数接口。但是，此时基类指针实际指向派生了对象，所以发生了多态。也即MockClass的mock method被实际调用。
- 以上两点是mock method能起作用，且不改变原有代码的原因。

但是，如果不对虚函数重写, 还是按照原来的方式定义mock class/mock method，由于业务代码并不能改变，所以这里还是基类指针。
同时，由于不触发多态行为，所以mock method并不会实际起作用，还是会调用业务类的方法。mock失败。

这里参照gmock给出的建议，进行调整
1. In this case, instead of sharing a common base class with the real class, your mock class will be unrelated to the real class
2. but contain methods with the same signatures.(just don't add override)

由于没有了继承关系，这回导致一个问题就是，业务代码中使用FooClass没有问题，但是测试代码中必须使用MockClass，这代表着必须改变业务代码接口。因为，这两个类已经没有关系了。
已经是通过基类的指针指向派生类来避免，但是现在不行了。

官方文档给了建议：
1. One way to do it is to templatize your code
2. you will give your code a template type argument for the type
3. In production, you will instantiate your template with FooClass as the type argument. In tests, you will instantiate the same template with MockFooClass
