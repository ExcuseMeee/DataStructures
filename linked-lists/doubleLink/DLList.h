#ifndef DLLIST_H
#define DLLIST_H
#include "DLLNode.h"


// WITH SENTINEL NODE IMPLEMENTED

template<typename T>
class DLList {
public:
  DLList(); // constructor
  ~DLList(); // destructor
  DLList(const DLList<T>& other); // copy constructor

  DLList<T>& operator=(const DLList<T>& other); // assignment(=) operator

  unsigned size() const; // return size of linked list
  bool empty() const; // return true if list is empty false otherwise

  void push_front(const T& value); // insert at beginning of list
  void push_back(const T& value); // insert at end of list
  void pop_front(); // remove the node at the beginning of the list
  void pop_back(); // remove the node at the end of the list
  void insert(unsigned position, const T& value, unsigned n = 1); // insert node n times at specified position
  void erase(unsigned position); // delete node at specified position
  void clear(); // clear all nodes
  void print() const;
  void print_backwards() const;

private:
  DLLNode<T>* head; // SENTINEL NODE: points to first node
  DLLNode<T>* tail; // SENTINEL NODE: points to last node
  unsigned listSize;

};


#endif