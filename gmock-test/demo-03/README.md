本小节在demo-02的基础上，采用了lucuszhang建议的非常tricky的手法，完成了测试
这种对client code 侵入非常小，只增加一个头文件, 相对可以接受。
本次实践在编译的时候，花了我一点时间，这里的编译也需要特别小心.

下面我给出具体的步骤:

1. 定义mock__foo.h(给出MockClass定义以及宏替换, 宏替换通过条件编译控制)
2. client 当中include mock_foo.h
3. unit_test当中正常进行测试，没有变化
4. build unit_test时要特别主要两点：1.需要打开条件编译 2.client.cc加入objs当中，重新编译，不要依赖之前正常编译的结果
