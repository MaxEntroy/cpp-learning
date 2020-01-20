#ifndef QUE_H_
#define QUE_H_

#include <stdio.h>

#include <queue>

template<class T>
class Que {
 public:
  Que() {}

  // Inserts a new element at the end of the queue.
  void Enque(const T& e);

  // Remove the "oldest" element from the queue and return it.
  // Return 0 if the queue is empty. Otherwise, return 1.
  int Deque(T* e);

  // Return the size of the queue.
  size_t size() const;

 private:
  std::queue<T> q_;

};

template<class T>
void Que<T>::Enque(const T& e) {
  q_.push(e);
}

template<class T>
int Que<T>::Deque(T* e) {
  if(q_.empty())
    return 0;

  *e = q_.front();
  q_.pop();

  return 1;
}

template<class T>
size_t Que<T>::size() const {
  return q_.size();
}

#endif
