## demo-01

基础demo，主要注意以下语法
- 继承机制的语法实现，member-specifier, virtual关键字
- 派生类构造的实现
- 派生类当中虚函数override
  - 声明建议加virtual(不加也可以，表明在基类当中就是virtual)
  - 实现不加virtual
- 多态机制的触发
  - 基类指针
  - 基类引用

## demo-02

q:redefined vs override
>在根目录README进行了介绍。本质上来说，redefined使用的底层机制
是static type checking，所以不会发生多态，及时基类的指针或者引用
指向派生类也没用。后者则是dynamic type checking，可用到rtti信息

## demo-03

本小节主要说析构函数不声明为virtual的问题
