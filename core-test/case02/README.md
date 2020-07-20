### case02

这里讲一个对于core文件的调试过程

q:现象？
1. 产生core文件
2. 线上环境，没有.cc文件，只有binary

看到的debug信息如下
```cpp
#0  0x00007f95b0451e18 in ?? ()
#1  0x000000000070b666 in GetDescriptor (this=0x7f9586e38c90)
    at third_party/protobuf/include/google/protobuf/message.h:336
#2  foo_parser<XXDocInfo> (
    L=L@entry=0x7f95f7794378, info=..., key=...)
    at xx_folder/foo_indexer.h:75
```

我希望的是可以看到当时的变量情况，看下是什么case导致了core

q:步骤
1. where(bt)这个命令会列出程序崩溃时的堆栈信息，一层一层会有标号  #0  #1  #2 .......
2. f  N    //N是你想要切换的栈的标号，达到后可以用  ‘p  变量’  查看变量的值，以查找异常出现的原因
3. p val // 打印希望看到的变量
4. info args // 可以打印此时函数的参数

由于我本次的core刚好卡在函数第一句处，所以入参的信息对我特别重要。

q:对于给定地址的变量，如何打印？
1. 使用命令x/s address

参考<br>
[gdb调试常用实用命令和core dump文件的生成](https://www.cnblogs.com/bodhitree/p/6077119.html)
[https://stackoverflow.com/questions/14493707/display-value-found-at-given-address-gdb/14493796](https://stackoverflow.com/questions/14493707/display-value-found-at-given-address-gdb/14493796)