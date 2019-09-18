## 链接

- static lingking

.a文件，本质上和.o文件都属于elf当中的可重定位文件，所以，.a写到objs处即可
相对路径可识别
```
INC_DIR:=./inc
SRC_DIR:=./src
EXE_DIR:=./bin

TARGET:=$(EXE_DIR)/main
OBJS:= $(wildcard $(SRC_DIR)/*.cc) thirdparty/tmath/lib/libtmath.a

CC:=g++
CFLAGS:=-g -Wall -std=c++11

$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -rf $(TARGET)

这是一种形式，之前对这里的理解不是很清晰。既然是库，还是要靠linker进行链接。
这是我的一个理解，并没有验证过。

那么自然有下面这种写法，
```
INC_DIR:=./inc
SRC_DIR:=./src
EXE_DIR:=./bin

TARGET:=$(EXE_DIR)/main
OBJS:= $(wildcard $(SRC_DIR)/*.cc)

CC:=g++
CFLAGS:=-g -Wall -std=c++11
LDFLAGS:= -L./thirdparty/tmath/lib -ltmath

$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf $(TARGET)
```

其中，
>-L告诉ld库的路径
-l对相应的库进行链接
这里我有一个误解，我之前以为，-L是指定动态库的路径，-l链接动态库，但其实不是，静态库和动态库都通过这两个选项进行路径指定和链接

下面这篇文章还讲到了更多的问题，就是库依赖的问题。

当然，静态库的好处是，compile time把.a打入binary，run time不再受影响。所以，只要编译通过，不会出现执行时找不到符号的问题。

参考<br>
[浅析静态库链接原理](http://codemacro.com/2014/09/15/inside-static-library/)<br>