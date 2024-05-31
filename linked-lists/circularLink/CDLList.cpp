#include "CDLList.h"
#include <iostream>

// DLLNode<T>(value, prev, next)
// TAIL IS THE ANCHOR POINTER

template<typename T>
CDLList<T>::CDLList() {
  tail = nullptr;
  listSize = 0;
}

template<typename T>
CDLList<T>::CDLList(const CDLList<T>& other) {
  this->tail = nullptr;
  this->listSize = 0;
  DLLNode<T>* cur = other.tail->next; // start at other list's front
  do {
    this->push_back(cur->data);
    cur = cur->next;
  } while (cur != other.tail->next); // stop once we loop back to front
}

template<typename T>
CDLList<T>& CDLList<T>::operator=(const CDLList<T>& other) {
  this->clear();
  DLLNode<T>* cur = other.tail->next; // start at other list's front
  do {
    this->push_back(cur->data);
    cur = cur->next;
  } while (cur != other.tail->next); // stop once we loop back to front
  return *this;
}

template<typename T>
CDLList<T>::~CDLList() {
  //remove all nodes
  clear();
}

template<typename T>
unsigned CDLList<T>::size() const {
  return listSize;
}

template<typename T>
bool CDLList<T>::empty() const {
  return (listSize == 0);
}

template<typename T>
void CDLList<T>::push_front(const T& value) {
  if (empty()) {
    tail = new DLLNode<T>(value); // create the first node
    tail->next = tail->prev = tail; // solo node will point to itself
  }
  else {
    // node after tail would be the front in a circular list 
    tail->next = new DLLNode<T>(value, tail, tail->next); // point tail to new node. new node is after tail and before old front. 
    tail->next->next->prev = tail->next;
  }

  listSize++;
}

template<typename T>
void CDLList<T>::print() const {
  std::cout << "Printing: ";
  if (empty()) {
    std::cout << "Empty List" << std::endl;
    return;
  }

  DLLNode<T>* cur = tail->next; // start at front (which is tail->next)
  do {
    std::cout << cur->data << "->";
    cur = cur->next; // go to next node
  } while (cur != tail->next); // stop once we loop back to front
  std::cout << std::endl;
}

template<typename T>
void CDLList<T>::print_backwards() const {
  std::cout << "Printing backwards: ";
  if (empty()) {
    std::cout << "Empty List" << std::endl;
    return;
  }

  DLLNode<T>* cur = tail; // start at back (which is tail)
  do {
    std::cout << cur->data << "->";
    cur = cur->prev; // go to prev node
  } while (cur != tail); // stop once we loop back to the back
  std::cout << std::endl;
}

template<typename T>
void CDLList<T>::push_back(const T& value) {
  if (empty()) {
    push_front(value); // push_front() will handle empty case
  }
  else {
    // the new tail will be after the current tail (duh...)
    push_front(value); // push_front() to create new node that is after tail
    tail = tail->next; // set tail to this new node
    // DO NOT UPDATE SIZE!!! push_front already does that
  }
}

template<typename T>
void CDLList<T>::pop_front() {
  if (empty()) return;
  // the front node is after the tail (tail->next)
  DLLNode<T>* to_delete = tail->next;

  if (listSize == 1) {
    // if only one node, delete tail (tail is always the first node added)
    tail = nullptr;
  }
  else {
    tail->next = tail->next->next; // point tail to the node after the front node. tail->next is now the front node
    tail->next->prev = tail; // point the front node's prev to tail

  }
  listSize--;
  delete to_delete;

}

template<typename T>
void CDLList<T>::pop_back() {
  if (empty()) return;
  if (listSize == 1) {
    pop_front(); // pop_front will handle case
  }
  else {
    DLLNode<T>* to_delete = tail;
    tail->prev->next = tail->next; // point the node before tail to the front node (front node is tail->next)
    tail->next->prev = tail->prev; // set front node's prev to the node before tail. tail is now disconnected
    tail = tail->prev; // set tail to old tail's previous
    listSize--;
    delete to_delete;
  }

}

template<typename T>
void CDLList<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}
