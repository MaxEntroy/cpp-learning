#include <iostream>
#include <memory>

struct Sample {
 public:
  Sample() : content_(0) {}
  explicit Sample(int content) : content_(content) {
    std::cout << "Constructing Sample(" << content_ << ")" << std::endl;
  }

  ~Sample() {
    std::cout << "Deleting Sample(" << content_ << ")" << std::endl;
  }

private:
  int content_;
};

void TestRawPtr() {
  Sample* p0 = new Sample(1);
  Sample* p1 = new Sample(3);

  delete p0;
  delete p1;
}

void TestSmartPtr() {
  auto p0 = std::make_unique<Sample>(11);
  auto p1 = std::make_unique<Sample>(33);
}

int main(void) {
  TestRawPtr();
  TestSmartPtr();
  return 0;
}
