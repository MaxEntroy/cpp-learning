## Makefile

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

```

- dynamic binding

.so文件，elf当中属于shared object file，由于不在compile time进行linking，所以编译时不需要加入.so文件。
但是，由于run time时需要dynamic linkikng，compile time需要进行说明
>-L的作用：指定.so的寻找路径，当然ld有默认的，如果不放入默认路径，需要自己指定。-lsoname，指定run time是dynamic linking的文件
相对路径可识别
```
INC_DIR:=./inc
SRC_DIR:=./src
EXE_DIR:=./bin

TARGET:=$(EXE_DIR)/main
OBJS:= $(wildcard $(SRC_DIR)/*.cc)

CC:=g++
CFLAGS:=-g -Wall -std=c++11 -Lthirdparty/tmath/lib -ltmath

$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -rf $(TARGET)
```

参考<br>
[C++静态库与动态库](https://www.cnblogs.com/skynet/p/3372855.html)<br>