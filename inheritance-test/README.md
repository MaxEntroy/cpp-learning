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


