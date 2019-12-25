- demo-01

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


- demo-02

这个demo给出了一个标准的makefile写法，单target,没有多余的嵌套逻辑.
