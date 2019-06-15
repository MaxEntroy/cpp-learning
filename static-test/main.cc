#include <string>
#include <vector>
#include <iostream>

class Foo {
public:
    Foo() : val(0) {}


    static void show(const std::string& msg) {
        std::cout << msg << std::endl;
    }

    // wrong way
    // 1.从逻辑上来，是统一的对象
    // 2.从实现上来看，则不是。任何成员变量，访问时需要对象地址。因为成员变量(变量或者函数)的地址需要通过对象来获得
    // 2.1.内部通过this
    // 2.2.外部通过对象
    // 3.static function 没有this指针
    // 3.1.本质无法找到成员函数的地址
    // 3.2.如果要访问成员变量 需要从外部传入
    /*
    static void print() {
        int v = get_val();
        std::cout << v << std::endl;
    }*/

    static void print(const Foo& foo) {
        int v = foo.get_val();
        std::cout << v << std::endl;
    }

    void set_val(int val_in) { val = val_in;}
    int get_val() const {return val;}

private:
    int val;

};

int main(void) {
    const std::string s = "hello, world";
    Foo::show(s);

    Foo foo;
    foo.set_val(5);

    Foo::print(foo);

    return 0;
}
