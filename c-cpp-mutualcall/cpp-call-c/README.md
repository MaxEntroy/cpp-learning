## cpp-call-c

第一版实现
```c
// add.h
#ifndef ADD_H_
#define ADD_H_

int cadd(int a, int b);

#endif

// add.c
#include <stdio.h>
#include "add.h"

int cadd(int a, int b) {
    printf("c func: cadd called.\n");
    return a + b;
}

// sub.h
#ifndef SUB_H_
#define SUB_H_

int csub(int a, int b);

#endif

// sub.c
#include <stdio.h>
#include "sub.h"

int csub(int a, int b) {
    printf("c func: csub called.");
    return a - b;
}
```

```cpp
#include <iostream>

#include "add.h"
#include "sub.h"

int main(void) {
    int a = 3;
    int b = 4;

    int ret = cadd(3, 4);
    std::cout << "cadd: " << ret << std::endl;
    ret = csub(3, 4);
    std::cout << "csub: " << ret << std::endl;

    return 0;
}
```
生成c的静态库，
>gcc -c add.c
gcc -c sub.c
ar cqs libcal.a add.o sub.o

编译cpp，
>g++ -o main main.cc
/tmp/ccApveKg.o：在函数‘main’中：
main.cc:(.text+0x21)：对‘cadd(int, int)’未定义的引用
main.cc:(.text+0x5c)：对‘csub(int, int)’未定义的引用
collect2: error: ld returned 1 exit status

问题很明显，compile time失败。那么到底是编译/汇编阶段失败，还是linking阶段失败呢？我们可以试下
>g++ -c main.cc

没有问题，毕竟头文件都加了，声明没有问题。所以问题出在linking阶段找不到定义，那么我们linking静态库
>kang@ubuntu:~/workspace/myspace/git-personal/cpp-learning/c-cpp-mutualcall/cpp-call-c(master)$ g++ -Wall -o main main.cc -L. -lcal
/tmp/ccJ3lusM.o：在函数‘main’中：
main.cc:(.text+0x21)：对‘cadd(int, int)’未定义的引用
main.cc:(.text+0x5c)：对‘csub(int, int)’未定义的引用
collect2: error: ld returned 1 exit status


一样的问题，那就确定，确实linking阶段找不到定义。
不太明白啥情况，为什么找不到定义呢？那么，我们还是从编译/汇编阶段看起，执行如下命令：
>g++ -c main.c 
nm main.o
                 U __cxa_atexit
                 U __dso_handle
00000000000000d0 t _GLOBAL__sub_I_main
0000000000000000 T main
0000000000000093 t _Z41__static_initialization_and_destruction_0ii
                 U _Z4caddii
                 U _Z4csubii
                 U _ZNSolsEi
                 U _ZNSolsEPFRSoS_E
                 U _ZNSt8ios_base4InitC1Ev
                 U _ZNSt8ios_base4InitD1Ev
                 U _ZSt4cout
                 U _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
0000000000000000 b _ZStL8__ioinit
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc

我们可以看到，编译/汇编阶段的符号是：_Z4caddii 和 _Z4csubii，那么我们再看libcal.a里面的符号：
>add.o:
0000000000000000 T cadd
                 U puts
sub.o:
0000000000000000 T csub
                 U puts

看起来应该是对不上，由于我对g++编译出的产物不是很了结，但是我又不想直面去看。所以，写一个c的文件，来做验证，
```c
// test.c
#include <stdio.h>

#include "add.h"
#include "sub.h"

int main(void) {
    int a = 3;
    int b = 4;

    int ret = cadd(a, b);
    printf("cadd: %d\n", ret);
    ret = csub(a, b);
    printf("csub: %d\n", ret);

    return 0;
}
```

执行如下命令，并看结果，
>gcc -c test.c
nm test.o
                 U cadd
                 U csub
0000000000000000 T main
                 U printf

显然，这么看是对的上，即test.o和libcal.a里面的符号是对的上的，所以linking阶段可以找到定义。但是，main.o则对不上。
进一步进行验证
>gcc -Wall -o test test.c -L./ -lcal
编译通过，执行顺利

在对gcc/g++的特性有进一步了解之后（g++为了支持重载，对于函数名字的编译/汇编产物和gcc不同），我们知道，main.cpp是c++文件，用g++编译器编译时(gcc也是一样的结果)，会优先选择cpp的编译方式，也就是会用cpp的编译方式去编译add()、sub()函数（add.h, sub.h）所以，编译/汇编阶段产生的符号，是按照g++的方式产生的。然而，它们是.c文件，libcal.a用的是c语言的方式去编译生成的，所以会导致编译/汇编阶段产生的符号和linking阶段对不上。

解决办法就是，**当cpp调用c时（即以c的方式提供.so或者.a），对应c库的头文件，在cpp当中一律用extern "C"进行声明**，这样来保证编译/汇编阶段生成的符号，在linking阶段找得到对应的定义。

我们对main.cc进行修改，并查看编译/汇编阶段的符号：
```cpp
#include <iostream>

extern "C" {
#include "add.h"
#include "sub.h"
}

int main(void) {
    int a = 3;
    int b = 4;

    int ret = cadd(a, b);
    std::cout << "cadd: " << ret << std::endl;
    ret = csub(a, b);
    std::cout << "csub: " << ret << std::endl;

    return 0;
}
```
执行如下命令：
>g++ -c main.c && nm main.o
                 U cadd
                 U csub
                 U __cxa_atexit
                 U __dso_handle
00000000000000d0 t _GLOBAL__sub_I_main
0000000000000000 T main
0000000000000093 t _Z41__static_initialization_and_destruction_0ii
                 U _ZNSolsEi
                 U _ZNSolsEPFRSoS_E
                 U _ZNSt8ios_base4InitC1Ev
                 U _ZNSt8ios_base4InitD1Ev
                 U _ZSt4cout
                 U _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
0000000000000000 b _ZStL8__ioinit
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc

很明显，cadd和csub的符号变成了和libcal.a当中一样的符号，从而也从侧面印证了我的猜想
那么，我们继续执行如下命令：
>g++ -Wall -o main main.cc -L. -lcal
编译通过，执行正常。


参考<br>
[c语言和c++的相互调用](https://blog.csdn.net/qq_29344757/article/details/73332501)