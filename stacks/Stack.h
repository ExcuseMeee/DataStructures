#ifndef STACK_H
#define STACK_H

namespace StackArray {
  template<typename T>
  class Stack {
  public:
    Stack(unsigned capacity = 10);
    ~Stack();

    void push(const T& val);
    void pop();
    const T& top() const;
    bool empty() const;
    bool full() const;

  private:
    T* data; // pointer to array of data
    unsigned capacity; // capacity of data
    int t; // index of the top-most element of stack. empty stack has t= -1

  };
}

namespace StackList {
  template<typename T>
  class Stack {
  public:
    Stack(unsigned capacity = 10);
    ~Stack();

    void push(const T& val);
    void pop();
    const T& top() const;
    bool empty() const;

  private:
    // defining Node class within Stack (SLLNode)
    template<typename T2>
    class Node {
    public:
      T data;
      Node<T>* next;

      Node(const T& val){
        data = val;
        next = nullptr;
      }
    };

    // using Node class for StackList
    Node<T>* front; // represents top of stack, and front of list (front -> ... -> nullptr)

  };
}

#endif