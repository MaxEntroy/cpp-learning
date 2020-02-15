## inheritance

本小节来自于对于msdn的学习
[Inheritance (C++)](https://docs.microsoft.com/en-us/cpp/cpp/inheritance-cpp?view=vs-2019)

### Overview

q:什么是继承?
>New classes can be derived from existing classes using a mechanism called "inheritance".
从已经存在的类派生出新来的机制，叫做继承。显然对于像lua这样的语言，并不支持，因为没有这样的机制。
>
>我们说的机制又是指什么呢？其实就是语言有没有给你这样的能力，具体来说就是有没有语法支持

### Virtual Functions

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

参考<br>

[Virtual Destructor](https://www.geeksforgeeks.org/virtual-destructor/)<br>
[When to use virtual destructors?](https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors)

### Single Inheritance

q:inheriance语义是什么?(描述了一种怎样的逻辑关系)
> derived class has a "kind of" relationship with the base class.
>
>继承其实说了两个类型的关系，朴素的看，这两个类型存在一种部分和整体的逻辑关系。基类是整体，派生类是部分。代表了一种从一般到具体的过程。
但是从集合的角度来看，刚好反过来。基类是一个小集合，而派生类是一个大集合。

q:派生类是否可以访问基类？如何访问？
>从集合角度来说，基类是派生类的子集，所以派生类有能力访问基类。
通过scope-resolution operator(::)来访问。

### Multiple Base Classes

q:what is multi-inheritance model?
>In a multiple-inheritance model, A class can be derived from more than one base class

q:多重继承当中，基类申明的顺序有什么影响?
>The order in which base classes are specified is not significant except in certain cases where constructors and destructors are invoked.
>
>只会影响，基类进行构造和析构的顺序。这个顺序通常没什么问题，哪个基类先构造或者先析构没有关系。
除非，基类的构造和析构需要明确的先后关系时，此时这个顺序是影响的.

q:多重继承中，基类的声明顺序，有什么需要特别注意的地方？
>The order of specification of base classes can affect the memory layout of the class. 
Do not make any programming decisions based on the order of base members in memory.

q:多重继承有什么不尽如人意的地方？
>派生类中可能有基类的多份副本.

我们看一个例子:
```cpp
// queue.h
#ifndef CASHIER_LUNCH_QUEUE_H_
#define CASHIER_LUNCH_QUEUE_H_

#include <iostream>

#include "cashier_queue.h"
#include "lunch_queue.h"

class CashierLunchQueue :
  public CashierQueue, public LunchQueue {
 public:
  CashierLunchQueue() : CashierQueue(), LunchQueue() {
    std::cout << "CashierLunchQueue called." << std::endl;
  }
};

#endif

// cashier_queue.h
#ifndef CASHIER_QUEUE_H_
#define CASHIER_QUEUE_H_

#include <iostream>

#include "queue.h"

class CashierQueue : public Queue {
 public:
  CashierQueue() : Queue() {
    std::cout << "CashierQueue called." << std::endl;
  }
};

#endif

// lunch_queue.h
#ifndef LUNCH_QUEUE_H_
#define LUNCH_QUEUE_H_

#include <iostream>

#include "queue.h"

class LunchQueue : public Queue {
 public:
  LunchQueue() : Queue() {
    std::cout << "LunchQueue called." << std::endl;
  }
};

#endif

// cashier_lunch_queue.h
#ifndef CASHIER_LUNCH_QUEUE_H_
#define CASHIER_LUNCH_QUEUE_H_

#include <iostream>

#include "cashier_queue.h"
#include "lunch_queue.h"

class CashierLunchQueue :
  public CashierQueue, public LunchQueue {
 public:
  CashierLunchQueue() : CashierQueue(), LunchQueue() {
    std::cout << "CashierLunchQueue called." << std::endl;
  }
};

#endif

// main.cc
#include "cashier_lunch_queue.h"

int main(void) {
  CashierLunchQueue que;
  return 0;
}


/*
Queue constructor called.
CashierQueue called.
Queue constructor called.
LunchQueue called.
CashierLunchQueue called.
*/
```
通过上面代码的执行结果，我们可以发现
- CashierLunchQueue当中，存在Queue的两份副本
- 派生类只负责对直接基类(direct base)进行构造
- 派生类先执行基类的构造，再执行派生类构造
- 派生类执行基类构造的顺序按照声明继承基类的顺序执行

q:multiple inheritance不采用virtual inheritance，参数构造时有什么需要注意的?
>此时会产生diamond problem，所以在最终的派生类中有多份基类副本，要保证多份基类都得到构造才行。
此时的构造并无特别需要注意的，还是派生类负责直接基类的构造即可

我们看个例子

```cpp
// que.h
#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>

class Queue {
 public:
  Queue(int cnt) : que_cnt_(cnt) {
    std::cout << "Queue constructor called. que_cnt = " << que_cnt_ << std::endl;
  }

 private:
  int que_cnt_;
};

#endif

// cashier_que.h
#ifndef CASHIER_QUEUE_H_
#define CASHIER_QUEUE_H_

#include <iostream>

#include "queue.h"

class CashierQueue : public Queue {
 public:
  CashierQueue(int cashier_cnt, int cnt) :
    Queue(cnt), cashier_que_cnt_(cashier_cnt) {
    std::cout << "CashierQueue called. cashier_que_cnt = " << cashier_que_cnt_ << std::endl;
  }

 private:
  int cashier_que_cnt_;
};

#endif

// lunch_que.h
#ifndef LUNCH_QUEUE_H_
#define LUNCH_QUEUE_H_

#include <iostream>

#include "queue.h"

class LunchQueue : public Queue {
 public:
  LunchQueue(int lunch_cnt, int cnt) :
    Queue(cnt), lunch_que_cnt_(lunch_cnt){
    std::cout << "LunchQueue called. lunch_que_cnt = " << lunch_que_cnt_ << std::endl;
  }

 private:
  int lunch_que_cnt_;
};

#endif

// cashier_lunch_que.h
#ifndef CASHIER_LUNCH_QUEUE_H_
#define CASHIER_LUNCH_QUEUE_H_

#include <iostream>

#include "cashier_queue.h"
#include "lunch_queue.h"

class CashierLunchQueue :
  public CashierQueue, public LunchQueue {
 public:
  CashierLunchQueue(int cashier_lunch_cnt,
                    int cashier_cnt, int cashier_cnt1,
                    int lunch_cnt, int lunch_cnt1) :
    CashierQueue(cashier_cnt, cashier_cnt1),
    LunchQueue(lunch_cnt, lunch_cnt1),
    cashier_lunch_que_cnt_(cashier_lunch_cnt){
    std::cout << "CashierLunchQueue called. cashier_lunch_que_cnt = " << cashier_lunch_que_cnt_ << std::endl;
  }

 private:
  int cashier_lunch_que_cnt_;
};

#endif

// main.cc
#include "cashier_lunch_queue.h"

int main(void) {
  CashierLunchQueue que(111,1,2,11,22);
  return 0;
}

/*
Queue constructor called. que_cnt = 2
CashierQueue called. cashier_que_cnt = 1
Queue constructor called. que_cnt = 22
LunchQueue called. lunch_que_cnt = 11
CashierLunchQueue called. cashier_lunch_que_cnt = 111
*/
```

通过以上结果我们可以发现：
- multiple-inheritance不采用virtual inheritance时，与single-inheritance没有区别，派生类只负责直接基类的构造
- 最终派生类中的多份副本，的确需要各个直接基类的多次构造，来完成对于多份间接基类的构造

q:virtual inheritance当中的间接基类如何构造?
>显然，由于此时只有一份间接基类。所以，间接基类的构造不能交给直接基类去构造，因为会产生冲突(到底以哪个直接父类的构造为准呢？)
所以， 此时间接基类的构造由最终派生类完成。虽然形式上，直接基类还是要负责对于间接基类的构造，但是并不生效。

代码如下：
```cpp
// queue.h
#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>

class Queue {
 public:
  Queue(int cnt) : que_cnt_(cnt) {
    std::cout << "Queue constructor called. que_cnt = " << que_cnt_ << std::endl;
  }

 private:
  int que_cnt_;
};

#endif

// cashier_queue.h
#ifndef CASHIER_QUEUE_H_
#define CASHIER_QUEUE_H_

#include <iostream>

#include "queue.h"

class CashierQueue : virtual public Queue {
 public:
  CashierQueue(int cashier_cnt, int cnt) :
    Queue(cnt), cashier_que_cnt_(cashier_cnt) {
    std::cout << "CashierQueue called. cashier_que_cnt = " << cashier_que_cnt_ << std::endl;
  }

 private:
  int cashier_que_cnt_;
};

#endif

// lunch_queue.h
#ifndef LUNCH_QUEUE_H_
#define LUNCH_QUEUE_H_

#include <iostream>

#include "queue.h"

class LunchQueue : virtual public Queue {
 public:
  LunchQueue(int lunch_cnt, int cnt) :
    Queue(cnt), lunch_que_cnt_(lunch_cnt){
    std::cout << "LunchQueue called. lunch_que_cnt = " << lunch_que_cnt_ << std::endl;
  }

 private:
  int lunch_que_cnt_;
};

#endif

// cashier_lunch_queue.h
#ifndef CASHIER_LUNCH_QUEUE_H_
#define CASHIER_LUNCH_QUEUE_H_

#include <iostream>

#include "cashier_queue.h"
#include "lunch_queue.h"

class CashierLunchQueue :
  public CashierQueue, public LunchQueue {
 public:
  CashierLunchQueue(int cashier_lunch_cnt,
                    int cashier_cnt,
                    int lunch_cnt,
                    int cnt) :
    Queue(cnt),
    CashierQueue(cashier_cnt, cnt),
    LunchQueue(lunch_cnt, cnt),
    cashier_lunch_que_cnt_(cashier_lunch_cnt){
    std::cout << "CashierLunchQueue called. cashier_lunch_que_cnt = " << cashier_lunch_que_cnt_ << std::endl;
  }

 private:
  int cashier_lunch_que_cnt_;
};

#endif

// main.cc
#include "cashier_lunch_queue.h"

int main(void) {
  CashierLunchQueue que(333,11,22,0);
  return 0;
}

/*
Queue constructor called. que_cnt = 0
CashierQueue called. cashier_que_cnt = 11
LunchQueue called. lunch_que_cnt = 22
CashierLunchQueue called. cashier_lunch_que_cnt = 333
*/
```