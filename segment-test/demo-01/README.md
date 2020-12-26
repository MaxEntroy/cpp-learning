## variables and segment

这一小节，讨论下变量和其代码段之间的关系。我们通过一个例子来进行说明。

```cpp
/**
 * simple_section.c
 *
 * gcc -c simple_section.c
 * gcc 版本 4.8.5 20150623 (Red Hat 4.8.5-4) (GCC)
 */

const int const_global_var = 8;
int global_init_var = 16;
int global_uninit_var;

void foo() {
  static int static_local_init_var = 32;
  static int static_local_uninit_var;

  const int const_local_var = 64;
  static const int static_const_local_var = 128;

  int local_init_var = 256;
  int local_uninit_var;
}

int main(void) {
  foo();
  return 0;
}
```

执行如下命令```readelf -a simple_section.o```

```cpp
ELF 头：
  Magic：  7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (可重定位文件)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  入口点地址：              0x0
  程序头起点：              0 (bytes into file)
  Start of section headers:          368 (bytes into file)
  标志：             0x0
  本头的大小：       64 (字节)
  程序头大小：       0 (字节)
  Number of program headers:         0
  节头大小：         64 (字节)
  节头数量：         13
  字符串表索引节头： 10

节头：
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       0000000000000029  0000000000000000  AX       0     0     4
  [ 2] .rela.text        RELA             0000000000000000  000006f0
       0000000000000018  0000000000000018          11     1     8
  [ 3] .data             PROGBITS         0000000000000000  0000006c
       0000000000000008  0000000000000000  WA       0     0     4
  [ 4] .bss              NOBITS           0000000000000000  00000074
       0000000000000004  0000000000000000  WA       0     0     4
  [ 5] .rodata           PROGBITS         0000000000000000  00000074
       0000000000000008  0000000000000000   A       0     0     4
  [ 6] .comment          PROGBITS         0000000000000000  0000007c
       000000000000002d  0000000000000001  MS       0     0     1
  [ 7] .note.GNU-stack   PROGBITS         0000000000000000  000000a9
       0000000000000000  0000000000000000           0     0     1
  [ 8] .eh_frame         PROGBITS         0000000000000000  000000b0
       0000000000000058  0000000000000000   A       0     0     8
  [ 9] .rela.eh_frame    RELA             0000000000000000  00000708
       0000000000000030  0000000000000018          11     8     8
  [10] .shstrtab         STRTAB           0000000000000000  00000108
       0000000000000061  0000000000000000           0     0     1
  [11] .symtab           SYMTAB           0000000000000000  000004b0
       0000000000000198  0000000000000018          12    12     8
  [12] .strtab           STRTAB           0000000000000000  00000648
       00000000000000a2  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)
  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)
  O (extra OS processing required) o (OS specific), p (processor specific)

There are no section groups in this file.

本文件中没有程序头。

重定位节 '.rela.text' 位于偏移量 0x6f0 含有 1 个条目：
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
00000000001e  000f00000002 R_X86_64_PC32     0000000000000000 foo - 4

重定位节 '.rela.eh_frame' 位于偏移量 0x708 含有 2 个条目：
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000200000002 R_X86_64_PC32     0000000000000000 .text + 0
000000000040  000200000002 R_X86_64_PC32     0000000000000000 .text + 14

The decoding of unwind sections for machine type Advanced Micro Devices X86-64 is not currently supported.

Symbol table '.symtab' contains 17 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS simple_section.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5
     6: 0000000000000004     4 OBJECT  LOCAL  DEFAULT    5 static_const_local_var.17
     7: 0000000000000000     4 OBJECT  LOCAL  DEFAULT    4 static_local_uninit_var.1
     8: 0000000000000004     4 OBJECT  LOCAL  DEFAULT    3 static_local_init_var.172
     9: 0000000000000000     0 SECTION LOCAL  DEFAULT    7
    10: 0000000000000000     0 SECTION LOCAL  DEFAULT    8
    11: 0000000000000000     0 SECTION LOCAL  DEFAULT    6
    12: 0000000000000000     4 OBJECT  GLOBAL DEFAULT    5 const_global_var
    13: 0000000000000000     4 OBJECT  GLOBAL DEFAULT    3 global_init_var
    14: 0000000000000004     4 OBJECT  GLOBAL DEFAULT  COM global_uninit_var
    15: 0000000000000000    20 FUNC    GLOBAL DEFAULT    1 foo
    16: 0000000000000014    21 FUNC    GLOBAL DEFAULT    1 main
```

该命令给出了详细的符号信息，下面我们简单汇总下

| symbol | segment | 
| :-----:| :----: |
| const_global_var | .rodata |
| global_init_var | .data |
| global_uninit_var | COM |
| static_local_init_var.172 | .data |
| static_local_uninit_var.1 | .bss |
| static_const_local_var.17 | .rodata | 
| foo | .text |
| main | .text |

根据.o文件当中符号所属的段，我们按照变量的作用域进行划分，可以得到如下结论
- 全局变量
  - 初始化: 常量位于.rodata 非常量位于.data
  - 未初始化: 位于COMMON块。原则上讲，我们可以认为未初始化的全局变量位于.bss，实际中和编译器实现有关
  - 是否static修饰不影响全局变量所属的segment，因为static只会编译单元内部是否可见
- 局部变量
  - 非static变量：non-static local variables are maintained at run time on stack.(even it is const qualified)
  - static变量：
    - 初始化：常量位于.rodata,非常量位于.data
    - 未初始化：.bss

根据变量和代码段的关系，我们可以进一步得知
- 变量是否存在数据段(.data./.bss/.rodata)和变量的作用域没有关系，本质是和变量的生存期有关系
- 只有全局变量和静态局部变量会存储在数据段，其余变量会在运行时维护在程序的栈上。
- 对于全局变量和静态局部变量，分为以下三种子情况
  - 初始化常量：.rodata
  - 初始化变量: .data
  - 未初始化变量: .bss/COMMON

进一步讨论，我原本讨论这一小节的原因在于想知道，constexpr是否会将变量放入数据段，来保证compile-time initialization，看结果不是这样的。
1. 我的基础假设是，放入.rodata的数据，会保证compile-time initialization
2. 但实际我看了.o的内容，发现被constexpr修饰的变量，并没有放入.rodata。
3. 但是可以肯定的是，constexpr修饰的变量，肯定完成了compile-time initialization。但是，这又无法否定我的基础假设
4. 正确的办法，应该是看一个变量，是否在compile-time完成了initialization。
5. 如果我能确定基础假设，就保证，对于放入.rodata的数据，没有必要使用constexpr
