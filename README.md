# cpp-learning

- lua-call-c
- static-dynamic-linking
- c-cpp-mutualcall

以上三个项目是在解决c->lua->.so时总结的，有一下几点收货：1.对于编译过程的几个阶段有了一个基本了结，尤其是对于linking阶段的认知，对于排查问题非常有帮助，这其中，美团的那篇文章起到了非常重要的作用。2.c与cpp相互调用的一些问题，对于```extern "C"```明确了一种固定的用法。3.动态库和静态库混用踩的坑，真是血泪史，能用动态库就用动态库确实是对的。
