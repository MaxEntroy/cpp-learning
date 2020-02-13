#ifndef BASE_H_
#define BASE_H_

class Base {
 public:
  Base() {}
  virtual ~Base();

  virtual void NameOf();
  void InvokingClass();
};

#endif
