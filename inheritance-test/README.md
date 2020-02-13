## inheritance

本小节来自于对于msdn的学习
[Inheritance (C++)](https://docs.microsoft.com/en-us/cpp/cpp/inheritance-cpp?view=vs-2019)

### overview

q:什么是继承?
>New classes can be derived from existing classes using a mechanism called "inheritance".
从已经存在的类派生出新来的机制，叫做继承。显然对于像lua这样的语言，并不支持，因为没有这样的机制。
>
>我们说的机制又是指什么呢？其实就是语言有没有给你这样的能力，具体来说就是有没有语法支持

### virtual functions

q:什么是virtual function，他的语义又是什么?
>A virtual function is a member function that you expect to be redefined in derived classes.When you refer to a derived class object using a pointer or a reference to the base class, you can call a virtual function for that object and execute the derived class's version of the function.
>
>简单来说，我理解的虚函数的语义，是为了实现接口来准备。比如java当中的interface定义接口，然后派生类实现这个接口。就是这么个语义。
本质来说，提供了接口的语义。说的详细一点：
1.成员函数 
2.必须在继承层次中讨论，否则无意义
3.派生类中可以重写 
4.基类指针调用接口，实际调用的并不一定是基类对象的接口，而是其指向的派生类对象的接口

q:redefine vs override?
>注意，我们上文说的，虚函数本质是接口，在派生类当中希望redefine，此处的redefine指的是更通用意义上的redefine。只不过，
对于虚函数和非虚函数的redefine，导致我们进一步区别了redefine and override.


>Here are some basic differences:

>An **overloaded** function is a function that shares its name with one or more other functions, 
but which has a different parameter list. 
The compiler chooses which function is desired based upon the arguments used.

>An **overridden** function is a method in a descendant class 
that has a different definition than a virtual function in an ancestor class. 
The compiler chooses which function is desired based upon the type of the object being used to call the function.
>
>A **redefined function** is a method in a descendant class 
that has a different definition than a non-virtual function in an ancestor class. 
Don't do this. Since the method is not virtual, the compiler chooses which function to call based upon the static type of the object reference rather than the actual type of the object.

q:redefine and override各自底层依赖的机制是什么?
>redefine触发static type checking, 而override触发dynamic type checking.
- Static type checking means that type checking occurs at compile time. No type information is used at runtime in that case.
- Dynamic type checking occurs when type information is used at runtime. C++ uses a mechanism called RTTI (runtime type information) to implement this. The most common example where RTTI is used is the dynamic_cast operator which allows downcasting of polymorphic types

具体代码参考 virtual functions/demo-02

参考<br>
[Redefining vs. Overriding in C++](https://stackoverflow.com/questions/26743991/redefining-vs-overriding-in-c)<br>

q:virtual functions是否可以声明为global或者static?
>No.Because virtual functions are called only for objects of class types, 
you cannot declare global or static functions as virtual.
>
>虚函数在被调用时依赖调用它的实际对象信息。所以是依赖对象信息的。声明为static或者global没有对象信息

q:在派生类中，对于基类声明的虚函数，是否有必要继续声明为virtual?
>没必要。虚函数一经声明，在整个派生体系中都是虚函数。其实思考本质语义即可，本质是个接口的语义.
我再具体实现的时候，还是写上了virtual，主要是有提示的作用。

q:基类当中的虚函数是否一定要实现？
>是的。必须一定实现。否则类的定义不完整，又如何定义对象？当然，如果不想实现，定位了纯虚函数，实现为抽象类即可。
>
>Virtual functions in a base class must be defined unless they are declared using the pure-specifier.

q:oo的多态特性在cpp中是通过继承机制、虚函数，基类指针(引用)指向派生类对象并调用虚函数这3种语法特性来实现，是否缺一不可？
>前2者不必多说，我们直接考察最后一个特性。
1.必须是基类指针或者引用指向派生类对象
2.调用虚函数
如果不满足这2者，有可能导致explicit qualification.后者会根据static type checking来获取类型信息

q:oo多态，是否当有了基类指针指向派生类对象，调用虚函数，一定会触发？
>No.The virtual function-call mechanism can be suppressed by 
explicitly qualifying the function name using the scope-resolution operator (::).

```cpp
int main(void) {
  CheckingAccount checking_account(1000);
  SavingAccount saving_account(100);

  Account* p = &checking_account;
  p->PrintBalance();
  p->Account::PrintBalance();

  Account& r = saving_account;
  r.PrintBalance();
  r.Account::PrintBalance();

  return 0;
}
/*
Checking account balance: 1000
Error.Balance not available for base type.
Savings account balance: 100
Error.Balance not available for base type.
*/
```

q:基类(我们讨论基类肯定是在继承体系当中)和派生类的析构函数为什么一定要声明为virtual?

- 基类析构(nono-virtual)派生类析构(non-virtual)
```cpp
// base.h
#ifndef BASE_H_
#define BASE_H_

class Base {
 public:
  Base() {}
  ~Base();

  virtual void NameOf();
  void InvokingClass();
};

#endif

// derived.h
#ifndef DERIVED_H_
#define DERIVED_H_

#include "base.h"

class Derived : public Base {
 public:
  Derived() : Base() {}
  ~Derived();

  virtual void NameOf();
  void InvokingClass();

};

#endif

// main.cc
#include <iostream>

#include "base.h"
#include "derived.h"

int main(void) {

  Base* p_base = new Derived();       // 动态调用 dynamic type checking 异常析构，资源泄露
  Derived* p_derived = new Derived(); // 静态调用 static type checking 正常析构
  Derived a_derived;                  // 静态调用 static type checking 正常熊沟

  delete p_base;
  std::cout << "-------------" << std::endl;
  delete p_derived;
  std::cout << "-------------" << std::endl;

  return 0;
}

/*
Deleting Base.
-------------
Deleting Derived.
Deleting Base.
-------------
Deleting Derived.
Deleting Base.
*/
```

很明显，我们可以发现:
1.静态调用时，析构函数不声明为virtual并没有问题。多说一句，静态调用是指，用到static type checking
2.动态调用，只能析构基类，派生类无法析构。如果派生类中进行资源申请，则资源泄漏.

- 基类析构(virtual)派生类析构(non-virtual)

```cpp
/*
Deleting Derived.
Deleting Base.
-------------
Deleting Derived.
Deleting Base.
-------------
Deleting Derived.
Deleting Base.
*/
```

此时，派生类已经正常析构。派生类加了析构函数，我也进行了测试，结果一致。因此在基类增加析构函数即可.

q:为什么基类的析构不加virtual,派生类就不能正常析构？
>首先，更正一下，不是基类析构不加virtual，派生类就不能正常析构。当static type checking时，可以正常析构。
只有当进行dynamic type checking时，才不能析构。更详细一点：

>Deleting a derived class object using a pointer to a base class that has a non-virtual destructor results in undefined behavior. 

>首先，这么用是未定义行为，所以上面的理解，不完全正确。

>In most implementations, the call to the destructor will be resolved like any non-virtual code, meaning that the destructor of the base class will be called but not the one of the derived class, resulting in a resources leak.
>
>大部分编译器的实现，基类指针指向派生类对象，在派生类对象进行析构时，对于析构函数的调用类似于对于non-virtual函数的调用，即执行
static type checking，所以只调用了基类的析构函数。所以，对于基类的析构函数需要加上virtual

q:virtual destructor底层是怎么实现的？
>既然上文也提到，不加virtual的行为，类似于non-virtual函数。加了virtual的行为显然是有了虚函数底层机制的支持。当然，
我还没有仔细考究这部分，先到着了。我把加与不加的符号dump出来，发现符号表也是有变化的。

q:virtual function 与 rule of three是否矛盾?
>不矛盾。只不过当我们使用rule of three时，此时如果在继承层次里面，那么析构函数需要virtual声明，如果不在继承层次，不需要。
如果根本不用rule of three，也更谈不上加virtual.
