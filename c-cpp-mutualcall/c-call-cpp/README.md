## c-call-cpp
第一版实现
```cpp
// add.h
#ifndef ADD_H_
#define ADD_H_

int cppadd(int a, int b);

#endif

// add.cc
#include "add.h"
#include <iostream>

int cppadd(int a, int b) {
    std::cout << "cppadd called." << std::endl;
    return a + b;
}

// sub.h
#ifndef SUB_H_
#define SUB_H_

int cppsub(int a, int b);

#endif

// sub.cc
#include "sub.h"
#include <iostream>

int cppsub(int a, int b) {
    std::cout << "cppsub called." << std::endl;
    return a - b;
}
```

编译一个.a出来，
>g++ -c add.cc
g++ -c sub.cc
ar cqs libcal.a add.o sub.o

然后给出main函数，
```c
// main.c
#include <stdio.h>

#include "add.h"
#include "sub.h"

int main(void) {
    int a = 3;
    int b = 4;

    int ret = cppadd(a, b);
    printf("cppadd: %d\n", ret);

    ret = cppsub(a, b);
    printf("cppsub: %d\n", ret);

    return 0;
}
```

采用如下命令进行编译，
>gcc -Wall -o main main.c -L. -lcal
/tmp/ccQt4U03.o：在函数‘main’中：
main.c:(.text+0x21)：对‘cppadd’未定义的引用
main.c:(.text+0x47)：对‘cppsub’未定义的引用
collect2: error: ld returned 1 exit status

编译未通过，找不到定义。采用cpp-call-c当中的办法，通过看.o来判断原来是符号不一致导致的问题。
这里还有一个点需要说下，由于是cpp兼容c，所以总是cpp的一侧做兼容。

那么，由于libcal.a是用g++编译出来的，默认的情形，函数符号是会带参数类型的，所以这里需要调整。

我们尝试对于cpp当中的函数，用extern "C"进行声明，来采用c linkage

```cpp
#include "add.h"
#include <iostream>

extern "C" int cppadd(int a, int b) {
    std::cout << "cppadd called." << std::endl;
    return a + b;
}
```
再进行编译，
>g++ -c add.cc 
In file included from add.cc:1:0:
add.h: In function ‘int cppadd(int, int)’:
add.h:4:5: error: previous declaration of ‘int cppadd(int, int)’ with ‘C++’ linkage
 int cppadd(int a, int b);
     ^
add.cc:4:35: error: conflicts with new declaration with ‘C’ linkage
 extern "C" int cppadd(int a, int b) {

我们可以看到如上问题，也好理解，add.h当中的cppadd声明采用c++ linkage，但是定义又是c linkage，同一个函数标签，这样会编出两个符号，我猜测编译器是这么工作的。

那么，一个自然的想法是，在.h当中也增加，extern "C"的声明，但是这样也不行，因为最后头文件是main.c会使用的，gcc不支持extern "C"的语法，后者是g++支持的。
自然的想法是，在cpp当中，去掉.h的声明，
```cpp
#include <iostream>

extern "C" int cppadd(int a, int b) {
    std::cout << "cppadd called." << std::endl;
    return a + b;
}

```
再执行如下命令进行编译，
>gcc -Wall -o main main.c -L. -lcal
./libcal.a(add.o)：在函数‘cppadd’中：
add.cc:(.text+0x14)：对‘std::cout’未定义的引用
add.cc:(.text+0x19)：对‘std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)’未定义的引用
add.cc:(.text+0x1e)：对‘std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)’未定义的引用
add.cc:(.text+0x26)：对‘std::ostream::operator<<(std::ostream& (*)(std::ostream&))’未定义的引用
./libcal.a(add.o)：在函数‘__static_initialization_and_destruction_0(int, int)’中：
add.cc:(.text+0x57)：对‘std::ios_base::Init::Init()’未定义的引用
add.cc:(.text+0x66)：对‘std::ios_base::Init::~Init()’未定义的引用
./libcal.a(sub.o)：在函数‘cppsub’中：
sub.cc:(.text+0x14)：对‘std::cout’未定义的引用
sub.cc:(.text+0x19)：对‘std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)’未定义的引用
sub.cc:(.text+0x1e)：对‘std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)’未定义的引用
sub.cc:(.text+0x26)：对‘std::ostream::operator<<(std::ostream& (*)(std::ostream&))’未定义的引用
./libcal.a(sub.o)：在函数‘__static_initialization_and_destruction_0(int, int)’中：
sub.cc:(.text+0x59)：对‘std::ios_base::Init::Init()’未定义的引用
sub.cc:(.text+0x68)：对‘std::ios_base::Init::~Init()’未定义的引用
collect2: error: ld returned 1 exit status

编译过不去，因为.a里面用到了iostream的能力，由.o->.a的过程中，**我理解应该是没有把add.o,sub.o当中需要的cpp lib打进.a，.a相当于还是一个.o的汇总**，因此最终在进行binary生成时，需要linking对应的库。

再进行编译，
>gcc -Wall -o main main.c -L. -lcal -lstdc++
编译顺利，运行正常。

对于上述的.cpp不能写.h的问题，可以采用如下的方式，也能正常编译通过，运行正常
```cpp
#include <iostream>

extern "C" {
#include "add.h"
int cppadd(int a, int b) {
    std::cout << "cppadd called." << std::endl;
    return a + b;
}
}
```

参考<br>
[gcc编译cpp文件为什么要加-lstdc++](https://blog.csdn.net/iloveyousunna/article/details/78527071)
[c语言和c++的相互调用](https://blog.csdn.net/qq_29344757/article/details/73332501)