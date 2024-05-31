#include "Stack.h"
#include <iostream>


template<typename T>
Stack<T>::Stack() {
  front = nullptr;
}

template<typename T>
Stack<T>::~Stack() {
  while (!empty()) {
    pop();
  }
}

template<typename T>
void Stack<T>::push(const T& val) {
  if (empty()) {
    front = new Node<T>(val);
  }
  else {
    Node<T>* newFront = new Node<T>(val);
    newFront->next = front; // point new node's next to current front
    front = newFront; // set front to new node
  }
}

template<typename T>
void Stack<T>::pop() {
  if (empty()) throw std::string("Empty Stack");

  Node<T>* to_delete = front;
  if (front->next == nullptr) {
    // if front is the last element in stack
    front = nullptr;
  }
  else {
    front = front->next;
  }
  delete to_delete;
}
template<typename T>
const T& Stack<T>::top() const {
  if (empty()) {
    throw std::string("Empty stack");
  }
  else {
    return front->data;
  }
}
template<typename T>
bool Stack<T>::empty() const {
  return (front == nullptr);
}

template<typename T>
void Stack<T>::print() const {
  Node<T>* cur = front;
  std::cout << '[';
  while(cur != nullptr){
    std::cout << cur->data << " ";
    cur = cur->next;
  }

  std::cout << "]\n";
}
