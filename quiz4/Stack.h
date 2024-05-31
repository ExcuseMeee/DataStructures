#ifndef STACK_H
#define STACK_H


template <typename T>
class Stack {
public:
  Stack();
  ~Stack();

  void push(const T& val);
  void pop();
  const T& top() const;
  bool empty() const;
  void print() const;

private:
  template <typename T2>
  class Node {
  public:
    T data;
    Node<T>* next;
    Node(const T& val = T(), Node<T>* n = nullptr) : data(val), next(n) {};
  };
  Node<T>* front;
};

#endif