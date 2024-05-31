#ifndef SLLIST_H
#define SLLIST_H
#include "SLLNode.h"

template<typename T>
class SLList {
public:
  SLList(); // constructor
  ~SLList(); // destructor
  SLList(const SLList<T>& other); // copy constructor

  SLList<T>& operator=(const SLList<T>& other); // assignment(=) operator

  unsigned size() const; // return size of linked list
  bool empty() const; // return true if list is empty false otherwise

  void push_front(const T& value); // insert at beginning of list
  void push_back(const T& value); // insert at end of list
  void pop_front(); // remove the node at the beginning of the list
  void pop_back(); // remove the node at the end of the list
  void insert(unsigned pos, const T& value, unsigned n = 1); // insert n nodes at specified position
  void erase(unsigned pos); // delete node at specified position
  void remove(const T& value); // remove all instances of value in list
  void clear(); // clear all nodes
  void print() const;

  void rotate_right(unsigned k); // shifts elements towards the right k times

private:
  SLLNode<T>* head; // points to first node
  SLLNode<T>* tail; // last node
  unsigned listSize;

};


#endif