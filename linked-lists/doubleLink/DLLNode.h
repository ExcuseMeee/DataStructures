#ifndef DLLNODE_H
#define DLLNODE_H

template<typename T>
class DLLNode {
public:
  T data;
  DLLNode<T>* next;
  DLLNode<T>* prev;

  // T() is default template value
  DLLNode(const T& d = T(), DLLNode<T>* p = nullptr, DLLNode<T>* n = nullptr) {
    data = d;
    next = n;
    prev = p;
  }

};

#endif