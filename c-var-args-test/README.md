q:下面代码实现的有什么问题?

```c
void myprintf(const char* format, ...) {
  printf("myprintf called.\n");
  printf(format, __VA_ARGS__);
}
```

我们编译看下结果
```c
gcc -std=gnu99 -g -o main main.c
main.c: In function ‘myprintf’:
main.c:6:18: warning: __VA_ARGS__ can only appear in the expansion of a C99 variadic macro [enabled by default]
   printf(format, __VA_ARGS__);
                  ^
main.c:6:18: error: ‘__VA_ARGS__’ undeclared (first use in this function)
main.c:6:18: note: each undeclared identifier is reported only once for each function it appears in
main.c: In function ‘main’:
main.c:15:3: warning: implicit declaration of function ‘MYPRINT’ [-Wimplicit-function-declaration]
   MYPRINT("hello, world: %s\n", "var_list");
   ^
make: *** [main] 错误 1
```

对于问题排查，错误提示是最直接的信息。务必要弄懂，不要搞不懂就去看别的。
上面的问题说道，```__VA_ARGS__```这个宏只能出现在variadic macro当中，这个是什么？难道不能是一个函数.

q:什么是Variadic macro
>A variadic macro is a feature of some computer programming languages, especially the C preprocessor, whereby a macro may be declared to accept a varying number of arguments.

q:什么又是Variadic function?
>In mathematics and in computer programming, a variadic function is a function of indefinite arity, i.e., one which accepts a variable number of arguments. 

仔细分析直接的错误原因之后，我们发现，问题其实很简单。就是```__VA_ARGS__```这个宏，只能出现在什么是Variadic macro，而不能出现在Variadic function。我之前没有发现这个错误，是不了解到这一点。
所以，对于错误原因的仔细分析，是非常有用的。通过这个知识点，我们也发现，有时候，只能写宏而不能写函数的场景。

正确的做法：
```c
#define MYPRINT(format, ...) \
 printf("MYPINT called.\n"); \
 printf(format, ##__VA_ARGS__);
```


参考
[Variadic macro](https://en.wikipedia.org/wiki/Variadic_macro)<br>
