本小节参照[Google Mock(Gmock)简单使用和源码分析——简单使用](https://blog.csdn.net/breaksoftware/article/details/51384083)进行实现

下面对一些细节给出说明

- role/user.h: 给出接口协议
- control/biz.h,biz.cc: 给出业务逻辑实现
- 这个demo的场景是，业务逻辑依赖接口协议进行实现，但是拿不到接口定义，那么在进行测试的时候需要mock接口对象

具体实现mock对象的时候，关注如下workflow
- Writing the Mock Class
  - How to Define It
  - Where to Put It
- Using Mocks in Tests
- Setting Expectations
  - General Syntax
  - Matchers: What Arguments Do We Expect?
  - Cardinalities: How Many Times Will It Be Called?
  - Actions: What Should It Do?

下面是一些我的使用心得：
1. gmock并不给出implentation，对于函数行为更多关注actions.
2. where to put这里，同一个团队的同事，可以放到_test.cc当中。不过，由于MockClass可能在在多个业务类中使用，所以增加一个统一的接口也是合理的
