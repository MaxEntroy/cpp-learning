#include <iostream>
#include <vector>

// iter_sum的实现没有问题
// 但是考虑iter_sum这个模板，不能从迭代器当中获取类型
// 其实，迭代器类型是关联value_type的，这样实现相当于传递了冗余信息
template<class T, class Iter>
T iter_sum(const Iter& first, const Iter& last) {
    T sum = 0.0;
    Iter b = first;
    while(b != last) {
        sum += *b;
        ++b;
    }
    return sum;
}

void version1() {
    int arr_int[] = {1,2,3,4,5};
    double arr_double[] = {1.1, 1.2, 1.3, 1.4, 1.5};

    const int num_int = sizeof(arr_int)/sizeof(int);
    const int num_double = sizeof(arr_double)/sizeof(double);

    int sum_int = iter_sum<int, int*>(arr_int, arr_int + num_int);
    double sum_double = iter_sum<double, double*>(arr_double, arr_double + num_double);

    std::cout << "sum_int: " << sum_int << std::endl;
    std::cout << "sum_double: " << sum_double << std::endl;


    std::vector<int> vec_int(arr_int, arr_int + num_int);
    std::vector<double> vec_double(arr_double, arr_double+num_double);

    sum_int = iter_sum<int, std::vector<int>::iterator>(vec_int.begin(), vec_int.end());
    sum_double = iter_sum<double, std::vector<double>::iterator>(vec_double.begin(), vec_double.end());

    std::cout << "sum_int: " << sum_int << std::endl;
    std::cout << "sum_double: " << sum_double << std::endl;
}

// iter_sum1的实现也没问题
// 但是，实现成了重载函数
// 因为，如果只实现一个迭代器版本，那么如果传递指针类型，模板参数推到会出错,因为指针类型，不是一个class类型
// 这么做的问题是，所有需要兼容指针的函数，都需要实现个重载版本
template<class Iter>
typename Iter::value_type iter_sum1(const Iter& first, const Iter& last) {
    typedef typename Iter::value_type T;
    T sum = 0.0;
    Iter b = first;
    while(b != last) {
        sum += *b;
        ++b;
    }
    return sum;
}

template<class T>
T iter_sum1(const T* first, const T* last) {
    T sum = 0.0;
    const T* p = first;
    while(p != last) {
        sum += *p;
        ++p;
    }
    return sum;
}

void version2() {
    int arr_int[] = {1,2,3,4,5};
    double arr_double[] = {1.1, 1.2, 1.3, 1.4, 1.5};

    const int num_int = sizeof(arr_int)/sizeof(int);
    const int num_double = sizeof(arr_double)/sizeof(double);

    int sum_int = iter_sum1<int>(arr_int, arr_int + num_int);
    double sum_double = iter_sum1<double>(arr_double, arr_double + num_double);

    std::cout << "sum_int: " << sum_int << std::endl;
    std::cout << "sum_double: " << sum_double << std::endl;

    std::vector<int> vec_int(arr_int, arr_int + num_int);
    std::vector<double> vec_double(arr_double, arr_double+num_double);

    sum_int = iter_sum1<std::vector<int>::iterator>(vec_int.begin(), vec_int.end());
    sum_double = iter_sum1<std::vector<double>::iterator>(vec_double.begin(), vec_double.end());

    std::cout << "sum_int: " << sum_int << std::endl;
    std::cout << "sum_double: " << sum_double << std::endl;
}

// iter_sum3的实现非常巧妙
// 对于上面的情形，只要有需要兼容指针和迭代器的类型，所有函数都需要重载
// 但是，下面的实现，通过iter_traits统一了迭代器的类型，让他们可以提供迭代器类型
// 具体的做法是全特化/偏特化
// 模板的形参不再是形参，而是有确定类型
template<class Iter>
struct iter_traits {
    typedef typename Iter::value_type T;
};

template<class Type>
struct iter_traits<Type*> {
    typedef Type T;
};

template<class Iter>
typename iter_traits<Iter>::T iter_sum3(const Iter& first, const Iter& last) {
    typedef typename iter_traits<Iter>::T T;
    T sum = 0.0;
    Iter b = first;
    while(b != last) {
        sum += *b;
        ++b;
    }
    return sum;
}

void version3() {
    int arr_int[] = {1,2,3,4,5};
    double arr_double[] = {1.1, 1.2, 1.3, 1.4, 1.5};

    const int num_int = sizeof(arr_int)/sizeof(int);
    const int num_double = sizeof(arr_double)/sizeof(double);

    int sum_int = iter_sum3<int*>(arr_int, arr_int + num_int);
    double sum_double = iter_sum3<double*>(arr_double, arr_double + num_double);

    std::cout << "sum_int: " << sum_int << std::endl;
    std::cout << "sum_double: " << sum_double << std::endl;

    std::vector<int> vec_int(arr_int, arr_int + num_int);
    std::vector<double> vec_double(arr_double, arr_double+num_double);

    sum_int = iter_sum1<std::vector<int>::iterator>(vec_int.begin(), vec_int.end());
    sum_double = iter_sum1<std::vector<double>::iterator>(vec_double.begin(), vec_double.end());

    std::cout << "sum_int: " << sum_int << std::endl;
    std::cout << "sum_double: " << sum_double << std::endl;

}

int main() {
    //version1();
    //version2();
    version3();

    return 0;
}
