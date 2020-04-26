[TOC]

## Forward Declaration

我在这里补充一些这个语法点的一些易错的地方：
- You cannot allocate an incomplete type, as the compiler doesn't know how big it is yet. This is solved by only using pointers to incomplete types.
- You cannot reference the members of an incomplete type before it's definition is seen by the compiler. This is solved by separating your interface and implementation in to header and code files.
- If you are in a situation where you have to use an incomplete type, you're probably doing something wrong. Try to avoid circular references wherever possible.

## 实践

- demo-01

一个相互引用的问题，pimpl idiom，当然，这么做的原因是为了让class impl能进行单元测试

q:既然相互引用时，采用forward declaration只能声明类型的指针和引用，而不能使用类型的任何具体实现，那这样相互引用还有什么用？虽然能过编译，但是最终的不能调用实际的方法，有什么用?
>这里在理解上有一个问题，forward declaration只是为了解决header file相互引用无限展开的问题，但是cpp source file不存在这个问题，所以声明的时候暂时使用forward declaration来通过编译
cpp source file包括头文件来给出complete type.

参考<br>
[C++ Forward declaration and 'Incomplete type is not allowed' error](https://stackoverflow.com/questions/15076026/c-forward-declaration-and-incomplete-type-is-not-allowed-error)
