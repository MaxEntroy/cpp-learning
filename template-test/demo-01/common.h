#ifndef COMMON_H_
#define COMMON_H_

template<class T>
T max(const T& lhs, const T& rhs) {
  return (lhs < rhs)?rhs:lhs;
}

#endif
