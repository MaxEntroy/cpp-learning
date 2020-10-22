本小节在demo-02的基础上，采用了lucuszhang建议的非常tricky的手法，完成了测试
这种对client code 侵入非常小，只增加一个头文件, 相对可以接受。
本次实践在编译的时候，花了我一点时间，这里的编译也需要特别小心.

下面我给出具体的步骤:

1. 定义mock__foo.h(给出MockClass定义以及宏替换, 宏替换通过条件编译控制)
2. client 当中include mock_foo.h
3. unit_test当中正常进行测试，没有变化
4. build unit_test时要特别主要两点：1.需要打开条件编译 2.client.cc加入objs当中，重新编译，不要依赖之前正常编译的结果

之前编译的问题，我在这里总结下：
1.现象，biz_test在进行编译的时候，打开mock_test编译开关。这个很正常。但是biz编译的时候，没有打开这个开关
2.compile time失败，具体卡在linking时，找不到符号。

```
/home/kang/workspace/myspace/git-personal/cpp-learning/gmock-test/demo-03/control/biz.cc:11: undefined reference to `User::Online()'
/home/kang/workspace/myspace/git-personal/cpp-learning/gmock-test/demo-03/control/biz.cc:12: undefined reference to `User::Login(std::string const&, std::string const&)'
/home/kang/workspace/myspace/git-personal/cpp-learning/gmock-test/demo-03/control/biz.cc:18: undefined reference to `User::Pay(int)'
collect2: error: ld returned 1 exit status
```

我的疑问是，我在编译biz_test时，已经打开了这个开关。那么Biz(MockUser)这个类已经生效，此时调用该类的Pay，间接调用MockUser的mock method即可，为什么会调用到以上3个函数。

这里有特别重要的一点：其实这个问题很早也关注过，就是c/cpp为什么要区分头文件和源文件。这里就碰到这个问题，.h当中只有函数声明，其实一点用处都没有，真正的函数定义，全部都在.c/.cpp当中。
那么对于Biz这个类，我们分别来看，打开编译开关和不打开编译开关的区别。

```
// 关闭条件编译
                 U __cxa_atexit
                 U __dso_handle
                 U _GLOBAL_OFFSET_TABLE_
0000000000000000 t _GLOBAL__sub_I_biz.cc
0000000000000000 r .LC0
000000000000000e r .LC1
000000000000001c r .LC2
0000000000000000 T _ZN3Biz3PayERKSsS1_i(!!!Biz::Pay)
                 U _ZN4User3PayEi(!!!User::Pay)
                 U _ZN4User5LoginERKSsS1_(!!!User::Login)
                 U _ZN4User6OnlineEv(!!!User::Online)
                 U _ZNSt8ios_base4InitC1Ev
                 U _ZNSt8ios_base4InitD1Ev
                 U _ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate
                 U _ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
                 U _ZSt4cerr
0000000000000000 b _ZStL8__ioinit
0000000000000000 t _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc.part.1

// 打开条件编译
                 U __cxa_atexit
                 U __dso_handle
0000000000000000 V DW.ref.__gxx_personality_v0
                 U __dynamic_cast
                 U _GLOBAL_OFFSET_TABLE_
0000000000000000 t _GLOBAL__sub_I_biz.cc
                 U __gxx_personality_v0
0000000000000000 r .LC0
000000000000000e r .LC1
0000000000000000 r .LC2
0000000000000060 r .LC3
0000000000000015 r .LC4
000000000000001b r .LC5
0000000000000029 r .LC6
000000000000002d r .LC7
                 U _Unwind_Resume
0000000000000000 T _ZN3Biz3PayERKSsS1_i(!!!BizPay)
                 U _ZN7testing8internal25UntypedFunctionMockerBase15SetOwnerAndNameEPKvPKc
                 U _ZN7testing8internal25UntypedFunctionMockerBase17UntypedInvokeWithEPKv
                 U _ZN7testing8internal6IsTrueEb
                 U _ZN7testing8internal8GTestLogC1ENS0_16GTestLogSeverityEPKci
                 U _ZN7testing8internal8GTestLogD1Ev
                 U _ZNSt8ios_base4InitC1Ev
                 U _ZNSt8ios_base4InitD1Ev
                 U _ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate
                 U _ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
                 U _ZSt4cerr
0000000000000000 b _ZStL8__ioinit
0000000000000000 t _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc.part.3
0000000000000000 V _ZTIN7testing8internal18ActionResultHolderIbEE
0000000000000000 V _ZTIN7testing8internal29UntypedActionResultHolderBaseE
0000000000000000 V _ZTSN7testing8internal18ActionResultHolderIbEE
0000000000000000 V _ZTSN7testing8internal29UntypedActionResultHolderBaseE
                 U _ZTVN10__cxxabiv117__class_type_infoE
                 U _ZTVN10__cxxabiv120__si_class_type_infoE
```

从上面的编译结果来看，我们可以很清楚的发现
1. 是否打开编译开关，导致Biz(User)和Biz(MockUser)的编译符号在User侧完全不同。Biz::Pay是一样的，但是不同的Biz Class，Biz::Pay调用的Login/Online/Pay符号是不同的。
2. 如上，源文件才是真正的函数执行代码。所以，biz_test进行编译后，调用BizPay。显然，定义是在.cc当中，但是这个biz.cc在编译的时候带着的是未打开编译开关的biz.h，所以编译的符号如第一段结果。
3. 所以，问题的真正原因是，biz_test当中的Biz::Pay，实际调用的是biz.cc当中的符号(BizPay)，但是这段代码编译时，未打开编译开关，导致Biz::Pay实际调用的是User::Pay/User::Login/User::Online，所以找不到定义。
4. 解决的办法是，在编译biz.cc的时候，打开编译开关，此时Biz::Pay调用的是MockUser::Pay/MockUser::Login/MockUser::Online，这些符号的定义是存在的，就不会出现错误。并且，调用的也是我们希望调用的mock方法