#include <functional>
#include <string>
#include <iostream>

// c-style
// function pointer
// 存在类型安全问题
// 指针类型转换导致类型安全问题
typedef void (*CallbackFunc) (const std::string&);
void f_callback(CallbackFunc caller, const std::string& mes) {
    caller(mes);
}

// cpp-style
// std::function object
void callback(std::function<void (const std::string&)> caller, const std::string& mes) {
    caller(mes);
}

void show(const std::string& message) {
    std::cout << message << std::endl;
}

void showInt(int val) {
    std::cout << val << std::endl;
}

void test_function() {
    std::string mes = "hello, world";
    f_callback(show, mes);
    callback(show, mes);
}

int Add(int a, int b) {return a + b;}

class Foo {
public:
    int add(int a, int b) { return a + b; }
};

void test_bind() {
    // bind 绑定函数及其参数 生成一个可调用对象
    // 提前bind 一些参数
    auto caller = std::bind(Add, 10, std::placeholders::_1);
    int sum = caller(20);
    std::cout << sum << std::endl;

    Foo foo;
    auto caller1 = std::bind(&Foo::add, foo, 100, std::placeholders::_1);
    sum = caller1(200);
    std::cout << sum << std::endl;
}

int main(void) {
    //test_function();
    test_bind();
    return 0;
}
