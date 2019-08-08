## demo-01
- Install blade
- Make a dir as root
- Touch BLADE_ROOT
- Make your own dir and write some code
- Write BUILD, similar to makefile
- Run blade

言简意赅，所以采用了这种写法。具体的地方我说下。
BLADE_ROOT所在的路径，和项目目录并列，因为会生成编译产物的目录。
这样的操作，对于odin这样的项目是合适的，因为这个大项目种有许多子项目。


参考<br>
[Use Blade](http://km.oa.com/base/attachments/attachment_view/29633)<br>

## demo-02
确定了几个点：
- 相对路径从BLADE_ROOT所在目录开始
- Makefile时代的src,inc的写法，可能不适合blade
    - 参考rerank的构建方法，其他文件构建成Lib，最后和main.cc构建成binary

[Blade用户手册](https://usermanual.wiki/Pdf/bladeusermanual.1358018446.pdf)