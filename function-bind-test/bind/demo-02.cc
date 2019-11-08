#include <functional>
#include <iostream>
#include <string>
#include <typeinfo>

class Student {
public:
    Student(): age_(0) {}
    Student(const std::string& name, int age) : name_(name), age_(age) {}

    void show(int year) const {
        std::cout << "year: " << year << std::endl;
        std::cout << "name: " << name_ << ", age: " << age_ << std::endl;
    }

private:
    std::string name_;
    int age_;
};

void test1() {
    Student s1("kang", 18);
    Student s2("ruixin", 20);

    s1.show(2019);
    s1.show(2019);
}

void test2() {
    auto show_student = std::bind(&Student::show, std::placeholders::_1, 2019);
    std::cout << typeid(show_student).name() << std::endl;

    int age = 0;

    std::cout << typeid(age).name() << std::endl;
    //Student s1("kang", 18);
    //Student s2("ruixin", 20);

    //show_student(s1);
    //show_student(s2);
}

int main(void) {
    // test1();
    test2();

    return 0;
}
