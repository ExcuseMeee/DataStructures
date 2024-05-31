#include <iostream>
#include "DLList.h"

template <typename T>
DLList<T>::DLList() {
  // create sentinel nodes
  head = new DLLNode<T>();
  tail = new DLLNode<T>();

  // IMPORTANT connect sentinel nodes
  head->next = tail;
  tail->prev = head;

  // list size is still 0
  listSize = 0;
}

template<typename T>
DLList<T>::~DLList() {
  clear(); // simply clear
}

template<typename T>
DLList<T>::DLList(const DLList<T>& other) {
  // init this list
  head = new DLLNode<T>();
  tail = new DLLNode<T>();
  listSize = 0;
  // connect sentinel nodes
  head->next = tail;
  tail->prev = head;

  // copy contents
  DLLNode<T>* cur = other.head->next;
  while (cur != other.tail) {
    push_back(cur->data);
    cur = cur->next;
  }

}

template<typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& other) {
  clear();

  // copy over contents to this list
  DLLNode<T>* cur = other.head->next;
  while (cur != other.tail) {
    push_back(cur->data);
    cur = cur->next;
  }

  return *this;
}

template<typename T>
unsigned DLList<T>::size() const {
  return listSize;
}

template<typename T>
bool DLList<T>::empty() const {
  return (listSize == 0);
}

template<typename T>
void DLList<T>::print() const {
  DLLNode<T>* cur = head->next;
  std::cout << "Printing list: ";
  while (cur != tail) {
    std::cout << cur->data << "->";
    cur = cur->next;
  }
  std::cout << "/" << std::endl;
}

template<typename T>
void DLList<T>::push_back(const T& value) {
  // DLLNode<T>(value, prev, next)
  tail->prev = new DLLNode<T>(value, tail->prev, tail); // set the last tail (tail->prev) to the newly made node. the new node's prev will be the old last tail (tail->prev) and its next will be the tail sentinel node
  (tail->prev)->prev->next = tail->prev; // connect the 2nd to last node (tail->prev->prev) to the new last node (tail->prev)
  listSize++;
}

template<typename T>
void DLList<T>::pop_front() {
  if (empty()) return;

  DLLNode<T>* to_delete = head->next; // store the first node to delete later
  head->next = (head->next)->next; // point the head node to the node after the first node (first node is head->next, so the node after is head->next->next)
  (head->next)->prev = head;
  listSize--;
  delete to_delete;
}

template<typename T>
void DLList<T>::pop_back() {
  if (empty()) return;

  DLLNode<T>* to_delete = tail->prev; // store the last node to delete later
  tail->prev = (tail->prev)->prev;
  tail->prev->next = tail;
  listSize--;
  delete to_delete;

}

template<typename T>
void DLList<T>::push_front(const T& value) {
  head->next = new DLLNode<T>(value, head, head->next);
  (head->next)->next->prev = head->next;
  listSize++;
}

template<typename T>
void DLList<T>::print_backwards() const {
  DLLNode<T>* cur = tail->prev;
  std::cout << "Printing list: ";
  while (cur != head) {
    std::cout << cur->data << "->";
    cur = cur->prev;
  }
  std::cout << "/" << std::endl;
}

template<typename T>
void DLList<T>::insert(unsigned position, const T& value, unsigned n) {
  if (position > listSize || position < 0 || n <= 0) return;
  if (position == 0) {
    for (int i = 0; i < n; i++) {
      push_front(value);

    }
  }
  else if (position == listSize) {
    for (int i = 0; i < n; i++) {
      push_back(value);

    }
  }
  else {
    DLLNode<T>* cur = head->next;
    // loop until the node BEFORE the specified position
    for (int i = 0; i < position - 1; i++) {
      cur = cur->next;
    }
    // add node n times
    for (int i = 0; i < n; i++) {
      cur->next = new DLLNode<T>(value, cur, cur->next); // connect current node to newly made node, new node should be after current and before current's next 
      cur->next->next->prev = cur->next; // connect the old cur->next's (which should now be cur->next->next) prev to the newly connected node (which should now be cur->next)
      cur = cur->next; // shift cur to new node
      listSize++;

    }
  }

}

template<typename T>
void DLList<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

template<typename T>
void DLList<T>::erase(unsigned position) {
  if (position < 0 || position > listSize - 1) return;
  if (position == 0) {
    pop_front();
  }
  else if (position == listSize - 1) {
    pop_back();
  }
  else {
    DLLNode<T>* cur = head->next;
    // find node at given position
    for (int i = 0; i < position; i++) {
      cur = cur->next;
    }
    cur->prev->next = cur->next; // connect the node before cur to the node after cur
    cur->next->prev = cur->prev; // connect the node after cur to the node before cur. cur is effectively unlinked now
    delete cur; // delete cur
    listSize--;
  }
}

template<typename T>
const T& DLList<T>::front(){
  if(empty()){
    throw std::string("Empty List"); // if empty throw error
  }
  return head->next->data;
}