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