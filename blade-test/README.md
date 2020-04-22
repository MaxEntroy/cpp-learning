[TOC]

## demo-01 安装

放了一个my_install文件，分析了install文件，发现这里的安装过程没有实际的编译过程。
其实项目里直接给到了编译产物，没有再安装的必要。
install脚本主要做了3件事
- 安装vim主题
- 安装bladefunctions
- 安装blade

当然，这里的安装没有编译的过程，只是单纯的拷贝

我修改了安装脚本，需要注意
- bash_profile根据自己的系统进行修改
- blade安装完毕，如果觉得$PATH展开太长，可以换回来，原始install就是展开的，没有修改

```shell
#!/bin/bash

blade_dir=$(cd $(dirname $0) && pwd)
cd $blade_dir

echo -n "Installing vim scripts..."
mkdir -p ~/.vim/{syntax,ftdetect,indent}
ln -sf $blade_dir/vim/ftdetect/* ~/.vim/ftdetect/
ln -sf $blade_dir/vim/syntax/* ~/.vim/syntax/
ln -sf $blade_dir/vim/indent/* ~/.vim/indent/
echo ", Done."

echo -n "Installing blade..."
echo "# blade-build-1.1.2" >> ~/.bash_profile
echo "export PATH=$PATH:$blade_dir" >> ~/.bash_profile
echo ", Done."

echo -n "Installing blade auxiliary tools..."
echo "test -s $blade_dir/bladefunctions && . $blade_dir/bladefunctions || true" >> ~/.bash_profile
echo ", Done."

echo -e "\033[1;32mAll successful, please log in again or source ~/.bash_profile manually\033[0m"
```

## demo-02 一个基本的demo
- Install blade
- Make a dir as root
- Touch BLADE_ROOT
- Make your own dir and write some code
- Write BUILD, similar to makefile
- Run blade

言简意赅，所以采用了这种写法。具体的地方我说下。
BLADE_ROOT所在的路径，和项目目录并列，因为会生成编译产物的目录。
这样的操作，对于odin这样的项目是合适的，因为这个大项目种有许多子项目。

[Blade用户手册](https://usermanual.wiki/Pdf/bladeusermanual.1358018446.pdf)
[Use Blade](http://km.oa.com/base/attachments/attachment_view/29633)<br>

## demo-03 makefile vs blade

### 头文件的作用

q:源文件不带.h有什么问题?(main.cc不带cal.h)
>preprocessing, assembly, compilation, linking四个阶段
compilation阶段，因为没有add函数的声明，所以该阶段无法通过.
当然，gcc和g++在这个问题上有不同，gcc -std=c99可以编译通过，只是告警。但是g++ -std=c++11则是error
我认为保持上面的理解没有问题

q:源文件不带.h有什么问题?(cal.cc不到cal.h)
>gcc std=c99这个编译器没有任何问题，编译通过。
正常情况下运行也没有问题。但是，一旦出现声明和定义不一致时，编译器无法提供更多信息，
源文件带.h是希望为编译器提供更多信息，帮助我们把更多的问题，暴露在compile time

```cpp
// cal.h
#ifndef CAL_H_
#define CAL_H_

// Add positive numbers.
//
// return 0 if any of the numbers are 0
// return -1 if any of the numbers are negative
int add(int left);

#endif

// cal.c
#include <stdio.h>

int add(int left, int right) {
  if(left < 0 || right < 0) {
    fprintf(stderr, "Can only add positive numbers, received %d and %d\n", left, right);
    return -1;
  }

  if(!left || !right)
    return 0;

  return left + right;
}

// main.c
#include <stdio.h>

#include "cal.h"

int main(void) {
  int ans = add(3);
  printf("ans = %d\n", ans);
  return 0;
}
/*
ans = 1537443131
运行结果很奇怪，因为没有传入right。
所以add执行时采用了垃圾值。
我们肯定不希望问题在run time暴露。
*/
```

如果cal.c当中加上```#include "cal.h"```，cal.h当中的声明和cal.cc当中的实现不一致的问题，就能就是发现

### makefile vs blade

- blade彻底解决以下两个问题
    - 头文件更新，受影响的模块没有重新构建。
    - 被依赖的库需要更新，而构建时没有被更新，比如某子目录依


我们先来看一个规范的Makefile
- main.o有依赖cal.h
- cal.o有依赖cal.h
```Makefile
CXX= g++ -std=c++11
CFLAGS= -Wall -Wextra -g $(MYCFLAGS)
LDFLAGS= $(MYLDFLAGS)
LIBS= $(MYLIBS)

MYCFLAGS=
MYLDFLAGS=
MYLIBS=

AR= ar rcu
RANLIB= ranlib
RM= rm -rf

MAIN_A= libmain.a
BASE_O= cal.o

MAIN_T= main
MAIN_O= main.o

# Targets start here
a: $(MAIN_A)

t: $(MAIN_T)

$(MAIN_A): $(BASE_O)
	$(AR) $@ $(BASE_O)
	$(RANLIB) $@

$(MAIN_T): $(MAIN_O) $(MAIN_A)
	$(CXX) -o $@ $(LDFLAGS) $(MAIN_O) $(MAIN_A) $(LIBS)

echo:
	@echo "CXX= $(CXX)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(LDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "AR= $(AR)"
	@echo "RANLIB= $(RANLIB)"
	@echo "RM= $(RM)"

clean:
	$(RM) $(MAIN_A) $(BASE_O) $(MAIN_T) $(MAIN_O)

.PHONY: a t echo clean

main.o: main.cc cal.h
cal.o: cal.cc cal.h
```

**如果在写Makefile依赖规则时，忘记少写了头文件**，那么头文件的更新不会引起依赖该头文件的模块进行
重新构建。因为Make不知道。

但是如果使用blade可以解决这个问题，因为blade具有一个特点：**自动分析头文件依赖关系，构建受影响的代码**
```Makefile
cc_binary(
  name = 'main',
  srcs = [
    'main.cc'
  ],
  deps = [
    ':main_lib'
  ]
)

cc_library(
  name = 'main_lib',
  srcs = [
    'cal.cc'
  ],
  deps = []
)
```

对比以上Makefile和BUILD发现：
- Makefile需要制定源文件的依赖关系，这其中包括头文件。但是blade则不需要，后者可以自动分析头文件依赖
- Makefile生成的.a需要写出完成的libmain.a，但是blade写lib名称即可。main_lib生成libmain_lib.a

q:blade编译选项在哪里?
>就好比，makefile可以指定编译的相关选项，那么blade是在哪里？
可以参看配置文件文档。BLADE_ROOT里面是当前项目，所以我也是采用这个方式。

```Makefile
cc_config(
  cxxflags = [
    '-std=c++11',
    '-g'
  ],
  warnings = [
    '-Wall',
    '-Wextra'
  ],
  optimize = [
    '-O3'
  ],
  extra_incs = [],
  linkflags = []
)
```

## demo-04 一个进阶项目

### 库的使用

其实对于库的使用，主要就是3点：
- 头文件路径(头文件怎么找)
- 库路径(库文件.a/.so怎么找)
- 库怎么链接

库的使用介绍两种情形，
- 项目自带，或者项目其它源文件编译而成的库
  - 头文件，从项目根目录写起即可(否则需要制定incs选项)。blade文档在工作空间组织中给出建议
  - 库路径，"//path/to/dir/:name"
  - 库怎么链接，用:进行链接。对于blade而言，项目自带库的链接，是以path:libname的形式给出，所以一举两得
- 系统库
  - 头文件，依赖环境变量，和makefile的写法没有区别
  - 库路径，同上。如果没指定，那就自己指定，extra_incs,link_flags
  - 库怎么链接，#name

### 库文件更新

显然,blade做的比Makefile好
- 库文件之间的依赖自动传递，一个库依赖另一个库，库的最终用户不需要关心
  - blade维护库之间的依赖，通常，应用程序只关心直接使用的库，而不关心间接使用的库
  - makefile则做不到，需要用户列出，用户程序使用的所有库
    - 比如，编写proto文件，生成xx_proto.a，应用程序直接依赖这个库。但是间接依赖的protobuf.a，也需要在makefile给出
- 库文件更新
  - 使用Makefile时，当某个库更新后，依赖它的目标重新构建时不会更新，只有先make clean才可以(makefile的规则是，只有precondition发生改变，target才会重新build,但是库不写到precondition当中，库是链接选项)
  - blade维护库之间的依赖关系，当某一个库更新后，依赖它的目标重新build时会自动更新

### 构建c++目标

#### cc_library(构建c++库目标)
```BUILD
cc_library(
  name = "cal",
  srcs = [
    "cal.cc"
  ],
  deps = []
)
```
cc_library同时用于构建静态和动态库，默认只构建静态库

#### cc_binary(构建c++可执行目标)

#### cc_test(测试目标)

```BUILD
cc_test(
  name = "cal_test",
  srcs = [
    "cal_test.cc"
  ],
  deps = [
    "//common:cal",
  ]
)
```

相当于cc_binary，再加上自动链接gtest和gtest_main。**这么做的前提是，cc_test_config配置正确**，默认是blade.conf里面的配置，一定要结合项目进行修改

### 构建prorobuf

**proto_library_config配置正确是前提**，否则找不到对应的库

```BUILD
proto_library(
  name = "cal_proto",
  srcs = [
    "cal_req.proto",
    "cal_res.proto"
  ],
  deps = []
)
```

## demo-05

这一小节主要测试defs的使用。主要引出了一些问题

1. 我之前的理解，.h和.cc生成一个.a/.so,由于.h要在.cc当中展开，所以.a/.so当中的代码，具备private/public的属性。目前来看，这种理解错误。但问题是，.h确实在.cc当中展开了，为什么此处对于pubic/private的声明无效？
2. 对于.a/.so的使用，需要使用对应的头文件。在此处传递defs，可以起到控制的作用。并且不同的client代码，相互独立。由于.h一样要在对应client代码中进行展开。所以不同的client会展开为不同的代码，这么做是灵活，也是合理的。不过背后的一些细节，比如1中提到的，还是对于编译的过程的理解不够到位

不过，在blade-test这个章节，不纠结这个问题，知道怎么传递defs测试private函数即可

## 总结

- blade优点
  - 自动维护库之间的依赖关系。makefile需要重新链接
  - 自动维护头文件间的依赖关系。makefile不自动维护，需要主动维护
  - 增量构建

- blade配置文件
  - blade 安装目录下的 blade.conf，这是全局配置。
  - ~/.bladerc 用户 HOME 目录下的 .bladerc 文件，这是用户级的配置。
  - BLADE_ROOT 其实也是个配置文件，写在这里的是项目级配置。
  - BLADE_ROOT.local 开发者自己的本地配置文件，用于临时调整参数等用途

一定要特别注意，自下而上的的进行覆盖，如果没有写单独配置，则会采用默认。至于默认是否符合项目要求，要自己判断

- BUILD文件编写
  - c/c++目标
    - cc_library
    - cc_binary
    - cc_test
  - protobuf

整个build过程，并不违背程序的compile time, run time过程。所以，也还是要结合makefile对比的看。
- compile time
  - preprocessing
  - compilation
  - assembly
  - linking
    - compile time需要找到符号的定义。不管是.a/.so都要在这个阶段提供其他符号定义
    - 编译通过，表明所有的符号都有声明，所有的符号都有定义。
    - 但是，至于库是否要在此时装入，则不一定。
      - compile time装入，就是static linking
- run time
  - linking
    - run time进行库的装入，就是dynamic linking.