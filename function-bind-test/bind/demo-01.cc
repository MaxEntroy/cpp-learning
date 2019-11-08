#include <functional>
#include <iostream>

int add(int a, int b) {return a + b; }

auto sub = [](int a, int b){return a - b;};

struct mul {
    int operator()(int a, int b){return a * b;}
};

class Foo {
public:
    Foo() : data_(-1) {}

    int get_data() const {return data_;}
    void set_data(int dat) {data_ = dat;}

private:
    int data_;
};

void bind_test() {

    auto fn_add = std::bind(add, std::placeholders::_1, 3);
    int ret = fn_add(5);
    std::cout << "ret = " << ret << std::endl;

    auto fn_sub = std::bind(sub, 3, std::placeholders::_1);
    ret = fn_sub(5);
    std::cout << "ret = " << ret << std::endl;

    auto fn_mul = std::bind(mul(), 3, 5);
    ret = fn_mul();
    std::cout << "ret = " << ret << std::endl;

    auto fn_mul1 = std::bind(mul(), std::placeholders::_1, std::placeholders::_2);
    ret = fn_mul1(3, 5);
    std::cout << "ret = " << ret << std::endl;

    Foo foo;
    auto fn_foo_get = std::bind(&Foo::get_data, &foo);
    ret = fn_foo_get();
    std::cout << "ret = " << ret << std::endl;

    auto fn_foo_set = std::bind(&Foo::set_data, &foo, std::placeholders::_1);
    fn_foo_set(10);
    std::cout << "ret = " << foo.get_data() << std::endl;

    auto fn_foo_set1 = std::bind(&Foo::set_data, &foo, 0);
    fn_foo_set1();
    std::cout << "ret = " << foo.get_data() << std::endl;
}

int main(void) {
    bind_test();

    return 0;
}
