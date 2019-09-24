## 总结
当我们讨论c->cpp或者cpp->c时，均默认被调方以.a或者.so的形式想client提供服务

- c->cpp
1.cpp编译成.a或者.so提供给c使用
2.cpp当中的函数，定义处需要用```extern "C"```进行声明。
3.cpp对应的.h不用上述声明
4.cpp如果用了cpp库，需要lstdc++

解释下第2点，main.c带着.h一起编译，所以编出来都是c-linkage符号，那么要求cpp当中的库函数，也采用c-linkage的方式进行编译.

- cpp->c
1.c编译成.a或者.so供cpp调用
2.cpp当中使用的.c对应的.h头文件，需要用```extern "C"```进行声明

解释下第2点，.a或者.so里面的符号就是c-linkage，那么cpp在编译的时候，如果默认进行，那么生成的是cpp-linkage的符号(编译/汇编阶段)，linking阶段在.a或者.so肯定是找不到对应符号的。

从上面，我们也可以看出些一致与区别，一致的是，始终都需要cpp来兼容c，不一致的是，二者的```extern "C"```使用的实际不一样。