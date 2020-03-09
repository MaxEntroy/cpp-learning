### blade是什么

- 构建工具,主要解决GNU make和autotools做的不好的地方
- Makefile的依赖如果没有写正确，每次需要make clean,项目较大时，降低效率

### blade解决的问题
- 源文件更新导致需要重新构建。这个 gnu make 都能解决得很好。
- 构建命令复杂，开发者可能需要理解命令行和各种参数。
- 头文件更新，所以依赖这个头文件的源文件都需要重新构建。这个 gnu make 不直接支持，需要搭配 gcc 来生成和更新依赖。
- 库文件更新，所依赖的库文件更新后，程序应该重新连接，GNU Make 可以做到。
- 即使我只构建自己的目标，如果库的源代码变了，库应该重新生成，GNU Make 用递归 Make 无法做到。
- 库文件之间的依赖自动传递，一个库依赖另一个库，库的最终用户不需要关心。
- 构建过程中的警告和错误应该醒目地显示出来。
- 能自动支持台风系统大量使用的 proto buffer，以及方便扩充以支持外来可能引入的新工具。
- 应该能集成自动测试，代码检查等开发常用的功能。

### blade代码组织

- 明确的根目录(BLADE_ROOT)
  - 有效地避免头文件重名造成的问题。
  - 有效地避免库文件的重名。
  - 更容易找到需要的文件。
  - 提高构建速度。

```cpp
$ ls -1
BLADE_ROOT
common
thirdparty
xfs
xcube
torca
your_project
...
```

### BUILD文件

我们先来回顾Makefile的写法
```makefile
<target> : <prerequisites> 
[tab]  <commands>
```

BUILD的写法大同小异，只不过BUILD没有Makefile那么通用，commands都是编译命令。
所以，只需写清楚target和prerequisites即可
一个基本的结构如下：
```BUILD
cc_library(
  name = 'string',
  srcs = [
      'algorithm.cpp',
      'string_number.cpp',
      'string_piece.cpp',
      'format.cpp',
      'concat.cpp'
  ],
  deps = ['//common/base:int']
)
```

Blade用一组**target函数**来定义目标，这些target的通用属性有：
- name: 字符串，和路径一起成为target的唯一标识，也决定了构建的输出命名
- srcs: 列表或字符串，构建该对象需要的源文件，一般在当前目录，或相对于当前目录的子目录中
- deps: 列表或字符串，该对象所依赖的其它targets

deps的允许的格式：
"//path/to/dir/:name" 其他目录下的target，path为从BLADE_ROOT出发的路径，name为被依赖的目标名。看见就知道在哪里。
":name" 当前BUILD文件内的target， path可以省略。
"#name" 系统库。直接写#跟名字即可，比如#pthread，#z分别相当于链接命令行上的-lpthread和-lz，但是会被传递给依赖这个库的其他目标。

对于系统库的定义并不准确，我写的第三方库也可以放到系统库的位置，所以还是从库的位置来说。项目内的库，都用:描述，否则用#描述。

### 配置文件

Blade 只有一种配置文件格式，但是支持多重配置文件，按以下顺序依次查找和加载，后加载的配置文件里存在的配置项会覆盖前面已经加载过的配置项

- 全局级别配置。blade 安装目录下的 blade.conf，这是全局配置。
- 用户级别配置。~/.bladerc 用户 HOME 目录下的 .bladerc 文件，这是用户级的配置。
- 项目级别配置。BLADE_ROOT 其实也是个配置文件，写在这里的是项目级配置。
- 文件级别配置。BLADE_ROOT.local 开发者自己的本地配置文件，用于临时调整参数等用途

对于配置文件的格式，有如下选项：
- global_config
- cc_config
- cc_test_config
- java_config
- proto_library_config
- thrift_config
