[TOC]

## Forward Declaration

我在这里补充一些这个语法点的一些易错的地方：
- You cannot allocate an incomplete type, as the compiler doesn't know how big it is yet. This is solved by only using pointers to incomplete types.
- You cannot reference the members of an incomplete type before it's definition is seen by the compiler. This is solved by separating your interface and implementation in to header and code files.
- If you are in a situation where you have to use an incomplete type, you're probably doing something wrong. Try to avoid circular references wherever possible.

参考
[C++ Forward declaration and 'Incomplete type is not allowed' error](https://stackoverflow.com/questions/15076026/c-forward-declaration-and-incomplete-type-is-not-allowed-error)