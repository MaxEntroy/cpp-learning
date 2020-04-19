#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_

namespace test {

class NonCopyable {
 protected:
  NonCopyable() {}
  virtual ~NonCopyable() {}

 private:
  NonCopyable(const NonCopyable&);
  NonCopyable& operator=(const NonCopyable&);
};

} // namespace test

#endif // NONCOPYABLE_H_

