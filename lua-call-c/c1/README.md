## lua-call-c

### 背景
这一小节，主要解决的是,c->lua，lua->.so的问题。主程序以及.so全部由c实现.
```
.
├── lib
│   ├── other_lib.c
│   └── other.so
├── main.c
├── Makefile
├── README.md
├── test.lua
└── thirdparty
    ├── liblua.so
    └── Makefile
```

```lib```存放的是测试.so的代码，具体的编译命令如下```gcc -fPIC -shared -o other.so other_lib.cc```<br>
```thirdparty```存放的是lua的动态库，版本是lua-5.3.0，Makefile也是修改后的版本，编译命令如下```make linux```<br>
```main.c/test.lua```主函数以及被调lua代码<br>

### 问题解决
对于这一问题的解决，主要经历了3个阶段<br>
1.1.编译的时候，找不到符号，诸如lua_createtable这种Lua CAPI找不到符号
>这一波主要是对compile/link有一个好的学习。当时以为是.so里面，由于用到了其他Lua CAPI，所以需要把.a打进来。后来知道，lua直接调用.so不存在这个问题，因为通过lua解释器，本身有这个环境。但是c->lua->.so时，此时需要，猜测大致是因为.so不能直接从lua环境里面找相关符号，所以需要.so自己把.a打进来，这个思路没有错，即.so还是需要Lua CAPI符号的支持，只不过后来冲突了

1.2.luaopen_xx找不到符号。这一波，主要是对c-cpp的相互调用，符号的问题，有了一个了解，对于extern "C"的学习
>具体的原因在于lua本质是c程序，.so用cpp写的，所以lua调用.so时，找不到luaopen_xx的符号，因为cpp进行编译的时候，为了支持重载，符号里面会带着参数类型

1.3.编译报错，多个虚拟机的问题。
>这个问题，直接搜了错误，发现应该是.so当中的.a和main.c生成的binary当中的.a冲突了，同一个程序，猜测lua应该不允许加载多个.a，会导致参考当中说的问题。所以解决办法就是打成一个.so来解决。

综上来看，对于1.1和1.2都是有确凿的知识需要学习，对于1.3则是要记住这个坑，**.so和.a不要混着用**

### 心得
这个问题着实让我花了些时间解决，好在自己没有放弃，一直在调整思路，持续追打，最终解决了这个问题。其实，目前阶段，我碰到的大部分问题，都不难，关键就是，自己的思路要清晰，每次要做出有效的试探才可以。还有，对于假设和假设验证到底谁有问题的判断，一定要在每一步拿到正确的结论，做出有效的试探，这才是解决问题的关键。不错，给自己点个赞，一步一步的思路都非常清晰，真是有一种山重水复疑无路，柳暗花明又一村的感觉。

**持续追打，保持清晰的思路，拿到正确的结论，做出有效的试探**这是解决问题的关键。


参考<br>
[在lua中调用 C模块(以及 multiple Lua VMs detected 错误的解决)](https://blog.csdn.net/qq_30949367/article/details/51405331)<br>
[multiple Lua VMs detected](https://blog.csdn.net/u010144805/article/details/80776802)<br>