#include <functional>
#include <iostream>

// callable object - function
int add(int a, int b) {return a + b;}


// callable object - lambda expression
auto sub = [](int a, int b){return a - b;};

// callable object - functor
struct mul {
    int operator()(int a, int b) {return a * b;}
};

void test_callable_object() {
    // all the callable object have the same signature int(int, int)
    std::function<int(int, int)> f_add = add;

    std::function<int(int, int)> f_sub = sub;

    std::function<int(int, int)> f_mul = mul();

    int left = 3;
    int right = 4;

    int ret = f_add(left, right);
    std::cout << "ret = " << ret << std::endl;

    ret = f_sub(left, right);
    std::cout << "ret = " << ret << std::endl;

    ret = f_mul(left, right);
    std::cout << "ret = " << ret << std::endl;
}

typedef std::function<int(int, int)> callback_t;
int test_callback(callback_t fn, int lhs, int rhs) {
    int ret = fn(lhs, rhs);
    return ret;
}
void test_callable_object1() {

    int lhs = 3;
    int rhs = 4;

    int ret = test_callback(add, lhs, rhs);
    std::cout << "ret = " << ret << std::endl;

    ret = test_callback(sub, lhs, rhs);
    std::cout << "ret = " << ret << std::endl;

    ret = test_callback(mul(), lhs, rhs);
    std::cout << "ret = " << ret << std::endl;
}

int main(void) {
    test_callable_object();

    test_callable_object1();
    return 0;
}
