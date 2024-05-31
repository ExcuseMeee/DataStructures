#ifndef SLLNODE_H
#define SLLNODE_H


template<typename T>
class SLLNode {
public:
  T data;
  SLLNode<T>* next;

  // T() is default template value
  SLLNode(const T& d = T(), SLLNode<T>* n = nullptr) {
    data = d;
    next = n;
  }
  
};

#endif