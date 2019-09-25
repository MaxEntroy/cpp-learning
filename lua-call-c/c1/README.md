## lua-call-c

lua本质是c程序，所以lua库用c实现，c->c没有问题。执行正常
>gcc -shared -fPIC -o other.so other_lib.c