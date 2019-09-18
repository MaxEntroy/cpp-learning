## 链接

- dynamic lingking

以下是错误的理解，颇具代表性，保留下来
>.so文件，elf当中属于shared object file，由于不在compile time进行linking，所以编译时不需要加入.so文件。
但是，由于run time时需要dynamic linkikng，compile time需要进行说明
-L的作用：指定.so的寻找路径，当然ld有默认的，如果不放入默认路径，需要自己指定。-lsoname，指定run time是dynamic linking的文件
相对路径可识别
```

之前没有发现这个问题，是因为之前的实验设置有问题，静态库和动态库在一起，所以当时的Makefile其实是.a发挥的作用。
第二篇参考文献，说的很清楚，**动态库的链接，两个阶段缺一不可**

q:既然dynamic linking，为什么还有编译时链接？
>首先，对于dynamic linking的理解有误。dynamic linking说的是库加入binary的时机，如果在compile time打到binary当中，即static linking
如果在run time才进行load，那么是dynamic linkikng，对应的库是.a和.so。所以，static linking和dynamic linking的区别是库装入的时机。
其次，如果编译时不进行linking，那么怎么解析符号呢？比如，我用了一个动态库提供的函数，但是compile time时，不告诉我这个库的任何信息，这个库函数的符号肯定是无法解析的。
所以，我的理解是，必须要进行编译时链接，是为了解决符号的问题。但是，此时库并不装入，还需要在run time时进行装入

q:对于static linking和dynamic lingking的概念比较混淆？
>这个概念是我自己总结的，所以犯了以前的问题，基础假设可能就存在问题。所以，这个不用纠结，还是要从本质上理解这个问题。
.a和.so的本质区别就是装入的时机。linking阶段要解决的一个很重要的问题就是，符号解析的问题。记住这2个点

下面，我们来看，如果编译时不进行链接出现的问题
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
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -rf $(TARGET)

/tmp/ccMVlBQO.o：在函数‘main’中：
/home/kang/workspace/myspace/git-personal/cpp-learning/static-dynamic-linking/dynamic-linking/./src/main.cc:8：对‘TAdd(int, int)’未定义的引用
/home/kang/workspace/myspace/git-personal/cpp-learning/static-dynamic-linking/dynamic-linking/./src/main.cc:11：对‘TMinus(int, int)’未定义的引用
collect2: error: ld returned 1 exit status
make: *** [bin/main] 错误 1
```

显然是符号解析的问题，找不到符号。

那么，我们进行修改，告诉compiler,linker需要什么库，和到哪找
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

g++ -o bin/main ./src/main.cc -g -Wall -std=c++11 -L./thirdparty/tmath/lib -ltmath
```
编译没有问题，但是执行的时候，会有如下问题
```
kang@ubuntu:~/workspace/myspace/git-personal/cpp-learning/static-dynamic-linking/dynamic-linking(master)$ ./bin/main 
./bin/main: error while loading shared libraries: libtmath.so: cannot open shared object file: No such file or directory
```

参考第二篇参考文献，对于Makefile进行修改：
```
INC_DIR:=./inc
SRC_DIR:=./src
EXE_DIR:=./bin

TMATH_DIR:=./thirdparty/tmath

TARGET:=$(EXE_DIR)/main
OBJS:= $(wildcard $(SRC_DIR)/*.cc)

CC:=g++
CFLAGS:=-g -Wall -std=c++11

LDFLAGS:= -L$(TMATH_DIR)/lib -Wl,-rpath=$(TMATH_DIR)/lib
LIBS:=-ltmath

$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS)

clean:
	rm -rf $(TARGET)
```
我并没有采用LD_LIBRARY_PATH的方法，考虑到这个库不通用，所以直接在Makefile当中修改了。但是原理是明白的，即-L参数指定的路径只在编译时有效，由于.so真正的
装入时机是在run time，所以需要binary也知道这个信息才可以，上面的办法，其实就是告诉binary这个信息。

多说一点，对于第三篇文献当中提到的这2个变量的区别，其实就很容易理解了。.so是需要两个阶段的链接，两个路径分别由两个环境变量来指定。

参考<br>
[C++静态库与动态库](https://www.cnblogs.com/skynet/p/3372855.html)<br>
[动态so库的链接：运行时链接和编译时链接](https://blog.csdn.net/u012247418/article/details/79729274)
[LIBRARY_PATH和LD_LIBRARY_PATH环境变量的区别](https://www.cnblogs.com/panfeng412/archive/2011/10/20/library_path-and-ld_library_path.html)