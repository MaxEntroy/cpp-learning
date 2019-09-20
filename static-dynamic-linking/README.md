## 误区

这一块的误区主要在于阶段比较多，对于一些环境变量的作用没有搞清楚是在哪个阶段起作用的。
我们先来看，compile time时，gcc的工作：
>When you invoke GCC, it normally does preprocessing, compilation, assembly and linking.  The "overall options" allow you to stop this process at an intermediate stage.  For example, the -c option says not to run the linker.  Then the output consists of object files output by the assembler.

从上面我们知道，compile time时，compiler主要是有4件事要做：preprocessing, compilation, assembly, linking.
其中，我目前理解到的，这里面又可以分为两个大阶段：
- 编译/汇编阶段
    - 实际经历preprocessing, compilation, assembly
    - 产物是.o
    - -c参数指定只运行这3个子阶段
- 链接阶段：
    - 实际经历linking阶段
    - 产物是.out

根据第一篇参考文献，我们知道，编译/汇编阶段，对于未定义的符号，只要给出它的声明即可，寻找该变量定义的工作是放在linking阶段去做
>我们在C源码文件部分曾经提到过，变量和函数的声明本质上是给编译器一个承诺，告诉编译器虽然在本文件中没有这个变量或者函数定义，但是在其他文件中一定有，所以当编译器发现程序需要读取这个变量对应的数据，但是在源文件中找不到的时候，就会把这个变量放在一个特殊的段（段类型为 U）里面，表示后续链接的时候需要在后面的目标文件或者链接库中找到这个变量，然后链接成为可执行二进制文件.
所以，我们也能知道，编译/汇编的产物是一定不能运行的。

同样的，linking阶段的工作，本质上就是对.o文件进行链接的过程，实际上是解决编译/汇编阶段声明未定义变量的问题，找到这些变量/函数的定义。

所以，我们可以暂时总结道，编译/汇编阶段，至少要找到变量的声明（这也是头文件的作用，头文件没有定义，只有声明，所以要放在编译阶段）。链接阶段则是要确定的找到声明变量/函数实际的定义。

那么，如下四个环境变量的作用，就很清晰了：

```c
export C_INCLUDE_PATH=$C_INCLUDE_PATH:/usr/local/thirdparty/lj-2.0.5/include
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/usr/local/thirdparty/lj-2.0.5/include
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/thirdparty/lj-2.0.5/lib
export LIBRARY_PATH=$LIBRARY_PATH:/usr/local/thirdparty/lj-2.0.5/lib
```

>前2个是在编译/汇编阶段，指定头文件去哪里找，是为了解决变量/函数的声明问题。
>LIBRARY_PATH是在linking阶段，指定.so的路径，找到只声明但未定义变量/函数的实际定义
>注意，上述3个变量，均只是在compile time发挥作用
>LD_LIBRARY_PATH是在run time发挥作用，功能和LIBRARY_PATH一致，指定.so的路径
>
>LIBRARY_PATH指定的路径只在编译时有效，编译出来的可执行文件并不知道.so的路径，所以在run time时还需要指定。

总结：
1.compile and run time是需要关注的两个阶段
2.compile time分为四个子阶段，但整体上可以看为两个阶段，编译/汇编，链接
3..so的linking比较特殊，需要在compile time/linking阶段指定路径，run time指定路径

参考<br>
[高级语言的编译：链接及装载过程介绍](https://tech.meituan.com/2015/01/22/linker.html?from=timeline&isappinstalled=0)<br>
[动态so库的链接：运行时链接和编译时链接](https://blog.csdn.net/u012247418/article/details/79729274)<br>
[LIBRARY_PATH和LD_LIBRARY_PATH环境变量的区别](https://www.cnblogs.com/panfeng412/archive/2011/10/20/library_path-and-ld_library_path.html)<br>