### demo-01

q:不带头文件，编译有什么影响？
>从下面的代码中，我们明显可以看出：
1.main.c缺少了foo.h
2.foo.c缺少了stdio.h
从编译结果来看，main.o,foo.o的编译，都提示了函数未声明的告警，但是并不是error，最后已编译没问题。
我的理解，可以的。
编译过程没问题，只是缺少另一个模块的函数。链接过程中，都有缺少函数的定义，也没问题。

```makefile
CC= gcc -std=gnu99
CFLAGS= -Wall -Wextra
LDFLAGS=
LIBS=

main: main.o foo.o
	$(CC) -o $@ $(LDFLAGS) main.o foo.o $(LIBS)

main.o: main.c
foo.o: foo.c

clean:
	rm -rf main main.o foo.o

.PHONY: clean
```

```c
// main.c
int main(void) {
    myprint("main", "hello, world");
    return 0;
}

// foo.c
void myprint(const char* pname, const char* msg) {
    printf("%s:%s\n", pname, msg);
}

```

编译结果
```makefile
gcc -std=gnu99 -Wall -Wextra   -c -o main.o main.c
main.c: In function ‘main’:
main.c:2:5: warning: implicit declaration of function ‘myprint’ [-Wimplicit-function-declaration]
     myprint("main", "hello, world");
     ^
gcc -std=gnu99 -Wall -Wextra   -c -o foo.o foo.c
foo.c: In function ‘myprint’:
foo.c:4:5: warning: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
     printf("%s:%s\n", pname, msg);
     ^
foo.c:4:5: warning: incompatible implicit declaration of built-in function ‘printf’ [enabled by default]
gcc -std=gnu99 -o main  main.o foo.o 
```

参考<br>
[warning-implicit-declaration-of-function(https://stackoverflow.com/questions/8440816/warning-implicit-declaration-of-function)

**结论**：没有头文件，一样可以运行。结合我这两天看书的心得，我们知道
- 源文件的编译都是相互独立的，如果遇见未定义的符号，待链接时计算该符号地址
- 链接时，对于未定义的符号，会在机器.o当中寻找，重新计算改符号地址。
从这个较多来说，有没有头文件，确实没什么帮助。

q:c/cpp为什么要采用头文件源文件这样的一种写法呢？java,c#,lua,python都没有这样实现？
>历史原因肯定是有的，可以仔细看看后面说的语言？java,lua,python都是解释型语言，不会生成.o这样的文件。
最直观的解释，接口和实现分离！这个是有道理的。
1.如果我写个第三方库，给你个.a，不给你.h，你怎么用？
2.编译器会帮我们做必要的检查，比如函数声明和函数定义是否匹配。如果没有，则不检查。执行时会core.

看下面代码，makefile保持不变
```c
// main.c
int main(void) {
    myprint("main");
    return 0;
}

// foo.c
void myprint(const char* pname, const char* msg) {
    printf("%s:%s\n", pname, msg);
}
/*
结果
main:}�?��
*/
```
很明显，输出了异常值。这本质上来说，破坏了栈空间，访问了垃圾值

如果我们加上头文件，则会有如下编译结果。即，编译器帮助我们检查了声明，和调用是否相符。提前帮助我们解决了问题。
```c
gcc -std=gnu99 -Wall -Wextra   -c -o main.o main.c
main.c: In function ‘main’:
main.c:3:5: error: too few arguments to function ‘myprint’
     myprint("main");
     ^
In file included from main.c:1:0:
foo.h:4:6: note: declared here
 void myprint(const char* pname, const char* msg);
      ^
make: *** [main.o] 错误 1
```

可以参考下，下面两个链接。
参考<br>
[为什么c++要“在头文件中声明，在源文件中定义”？](https://www.zhihu.com/question/58547318)<br>
[为什么C/C++要分为头文件和源文件？](https://www.zhihu.com/question/280665935)<br>
[C语言的头文件是必须的吗？](https://blog.csdn.net/blow_jj/article/details/42219709)

q:make的自动推到规则是怎样？
>在使用 make 编译.c 源文件时，编译.c 源文件规则的命令可以不用明确给出。
这是因为 make 本身存在一个默认的规则，能够自动完成对.c 文件的编译并生成对应的.o 文件
但是，executable file并没有自动推动规则，只有.c->.o的过程才有

参考<br>
[makefile最佳实践 - 从原理到实用技巧](https://segmentfault.com/a/1190000016176722)

q:这个demo学到那些技巧？
>整体思路来自lua的makefile:
1.c->.o交给自动推导
2..o可以写本项目的.h，libc的.h不写


### demo-02

这个demo给出了一个标准的makefile写法，单target,没有多余的嵌套逻辑.
层次逻辑如下：
- 第一层:.c->.o
- 第二层:.o集合定义 .a定义 target定义
- 第三层:target objs规则

对于demo-01中讨论的问题，我们来做更进一步的讨论：

- case1
这种情形，和demo-01一直，源文件都不带头文件，会有什么问题(makefile也不带)？
```
// main.c
int main(void) {
    myprint("main", "hello,world");
    return 0;
}

// foo.c
void myprint(const char* pname, const char* msg) {
    printf("%s:%s\n", pname, msg);
}

/*
gcc -std=gnu99 -Wall -Wextra    -c -o main.o main.c
main.c: In function ‘main’:
main.c:2:5: warning: implicit declaration of function ‘myprint’ [-Wimplicit-function-declaration]
     myprint("main", "hello,world");
     ^
gcc -std=gnu99 -Wall -Wextra    -c -o foo.o foo.c
foo.c: In function ‘myprint’:
foo.c:2:5: warning: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
     printf("%s:%s\n", pname, msg);
     ^
foo.c:2:5: warning: incompatible implicit declaration of built-in function ‘printf’ [enabled by default]
ar rcu libmain.a foo.o
ranlib libmain.a
gcc -std=gnu99 -o main  main.o libmain.a
*/
```
最后编译过程顺利，有warning，但是没有error.可以正常执行。原因也好理解，不用源文件都是独立编译，链接的时候，能找到目标符号即可。

q:既然源文件不用带头文件，也可以正常编译通过，那么带头文件有什么用？
>为什么要分头文件和源文件，已经在上文描述过。带头文件的是有额外的好处，能让编译器帮我们做更多的检查工作。
```cpp
// 如果函数调用和实现不一致，如果不带头文件。compile time没法发现这个错误，run time打印垃圾值，有进一步core的可能
// main.c
int main(void) {
    myprint("main");
    return 0;
}

// foo.c
void myprint(const char* pname, const char* msg) {
    printf("%s:%s\n", pname, msg);
}

// 加上头文件，compile time就可以发现这个问题，及时修复
// main.c
#include "foo.h"
int main(void) {
    myprint("main");
    return 0;
}

// foo.c
void myprint(const char* pname, const char* msg) {
    printf("%s:%s\n", pname, msg);
}
```

q:自身源文件加自身头文件的目的又为了什么？
>上面这个demo是其他源文件，加了对应函数的头文件，是为了让编译器做更多的检查。防止别人调用和实现不一致。自己加其实是一样的道理，防止自己的声明和实现不一致。从而避免提供错误的接口给别人。

```cpp
// foo.c
#include <stdio.h>
void myprint(const char* pname, const char* msg, int flag) {
    if(flag == 1) {
        printf("%s:%s\n", pname, msg);
    }
}

// foo.h
#ifndef FOO_H
#define FOO_H

void myprint(const char* pname, const char* msg);

#endif

// main.c
#include "foo.h"
int main(void) {
    myprint("main", "hello,world");
    return 0;
}
/*
执行结果什么都没有，调用者非常纳闷，根本不知道什么原因。我就是照着你接口写的。但是什么结果都没有输出。
*/
```

- 源文件包含其他头文件
     - 是为了确保调用和声明一致。
     - 否则，如果不包含，调用接口不一致，不能在compile time及时发现。run time可能core.
- 源文件包含自己的头文件
     - 是为了自己的声明和实现一致。
     - 否则，如果不包含，自己的声明和实现不一致，不能在compile time及时发现。run time可能core.

总结，.h和.c分离的原因我们是知道的。.c当中加.h的原因，我们在本节也搞清楚了。还是希望借助编译器的能力，把更多的问题在compile time就进行暴露。

q:Makefile不写.h又有什么问题？
>如果是第一次编译，没有问题。但是我们看下target进行重新构建的时机：只要有一个前置文件不存在，或者有过更新（前置文件的last-modification时间戳比目标的时间戳新），"目标"就需要重新构建.

具体的情况，我们分以下两种

- 库依赖自身头文件
     - 是为了确保声明和实现一致
     - 否则，如果声明头文件发生了修改，但是makefile没有依赖，库不会重新编译，此时声明和实现发生偏离，没有在compile time进行暴露。
     - 如果target依赖了库的文件，但是库没有依赖自身头文件，那么当我们修改库头文件和target时，编译正常。因为库自身没有触发重新编译，新的功能无法实现。
- target依赖其他库头文件
     - 是为了确保调用和声明一致
     - 否则，库的头文件和源文件发生变更，接口改变，但是target没有触发重新编译。问题没有在compile time及时发现，run time可能会触发core.

总结，makefile的依赖，写.h的好处在于，会触发重新编译，避免接口调用，接口声明，接口实现发生分离，但是在compile time无法暴露的问题。