#include <iostream>
#include <string>
#include "Stack.h"


template<typename T>
StackArray::Stack<T>::Stack(unsigned capacity) {
  this->capacity = capacity;
  this->data = new T[capacity];
  this->t = -1; // for an empty stack, the index of the first element... is -1 bc there is no element!
}
template<typename T>
StackArray::Stack<T>::~Stack() {
  delete[] data;
}
template<typename T>
void StackArray::Stack<T>::push(const T& val) {
  if (!full()) {
    data[++t] = val; // pre-increment (++t)
  }
  else {
    throw std::string("Full Stack");
  }
}
template<typename T>
void StackArray::Stack<T>::pop() {
  if (!empty()) {
    t--;
  }
  else {
    throw std::string("Empty Stack");
  }
}
template<typename T>
const T& StackArray::Stack<T>::top() const {
  if (!empty()) {
    return data[t];
  }
  else {
    throw std::string("Empty Stack");
  }
}
template<typename T>
bool StackArray::Stack<T>::empty() const {
  return t == -1;
}
template<typename T>
bool StackArray::Stack<T>::full() const {
  return t == capacity - 1; // the max index of t is capacity - 1
}


/*
--------------------------STACKLIST---------------------------------------------------
*/

template<typename T>
StackList::Stack<T>::Stack(unsigned capacity) {
  front = nullptr;
}


template<typename T>
StackList::Stack<T>::~Stack() {
  while (!empty()) {
    pop();
  }
}

template<typename T>
void StackList::Stack<T>::push(const T& val) {
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
void StackList::Stack<T>::pop() {
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
const T& StackList::Stack<T>::top() const {
  if (empty()) throw std::string("Empty Stack");
  return front->data;
}


template<typename T>
bool StackList::Stack<T>::empty() const {
  return (front == nullptr);
}