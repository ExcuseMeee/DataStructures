#include <iostream>
#include "SLList.h"


// NO SENTINEL NODE IMPLEMENTED

template<typename T>
SLList<T>::SLList() {
  head = nullptr;
  tail = nullptr;
  listSize = 0;
}

template<typename T>
SLList<T>::~SLList() {
  clear();
}

template<typename T>
SLList<T>::SLList(const SLList<T>& other) {
  // init this list
  head = nullptr;
  tail = nullptr;
  listSize = 0;

  // copy other list to this list
  SLLNode<T>* cur = other.head;
  while (cur != nullptr) {
    push_back(cur->data);
    cur = cur->next;
  }
}

template<typename T>
SLList<T>& SLList<T>::operator=(const SLList<T>& other) {
  clear(); // clear this list


  // copy other list to this list
  SLLNode<T>* cur = other.head;
  while (cur != nullptr) {
    push_back(cur->data);
    cur = cur->next;
  }

  return *this;
}

template<typename T>
unsigned SLList<T>::size() const {
  return listSize;
}

template<typename T>
bool SLList<T>::empty() const {
  return (listSize == 0);
}

template<typename T>
void SLList<T>::push_front(const T& value) {
  head = new SLLNode(value, head); // point old head to new node, while passing in old head to the next attribute of the new node
  listSize++; // increment listsize

  // set tail
  if (listSize == 1) {
    // very first node added to empty list is also the last
    tail = head;
  }

}

template<typename T>
void SLList<T>::push_back(const T& value) {
  SLLNode<T>* newTail = new SLLNode<T>(value);
  if (empty()) {
    head = newTail;
    tail = newTail;
  }
  else {
    tail->next = newTail; // point old tail to newly made node
    tail = newTail; // point tail value to newly made node, since this is the new tail

  }
  listSize++;
}

template<typename T>
void SLList<T>::print() const {
  SLLNode<T>* cur = head;
  std::cout << "Printing list: ";
  while (cur != nullptr) {
    std::cout << cur->data << "->";
    cur = cur->next;
  }
  std::cout << "/" << std::endl;
}

template<typename T>
void SLList<T>::pop_front() {
  if (empty()) return; // if empty do nothing

  SLLNode<T>* to_delete = head; // temporarily store current head to delete later
  head = head->next; // point head to the node after the head node
  if (listSize == 1) {
    // if tail and head are same (aka only 1 node in list), set tail to head (head should be nullptr)
    tail = head;
  }
  delete to_delete; // delete old head

  listSize--; // decrement size

}

template<typename T>
void SLList<T>::pop_back() {
  if (empty()) return; // if empty do nothing

  if (listSize == 1) {
    // if only 1 node, pop_front() should work just fine
    pop_front();
  }
  else {
    // find the 2nd to last node, then connect that to nullptr effectively disconnecting the last node
    SLLNode<T>* cur = head;
    while (cur->next->next != nullptr) {
      cur = cur->next;
    }
    SLLNode<T>* to_delete = tail; // temporarily store current tail to delete later
    cur->next = nullptr; // point 2nd to last node's next to nullptr. cur is now effectively the last node
    tail = cur; // point tail to cur
    delete to_delete; // delete old tail
    listSize--;
  }

}

template<typename T>
void SLList<T>::clear() {
  // just keep popping front until list is empty
  while (!empty()) {
    pop_front();
  }
}

template<typename T>
void SLList<T>::insert(unsigned pos, const T& value, unsigned n) {
  if (pos > listSize || pos < 0 || n <= 0) return; // is position is out of bounds do nothing, if n<=0 do nothing

  if (pos == 0) {
    for (int i = 0; i < n; i++) {
      push_front(value);
    }
  }
  else if (pos == listSize) {
    for (int i = 0; i < n; i++) {
      push_back(value);
    }
  }
  else {
    SLLNode<T>* cur = head;
    // find the node BEFORE the specified position
    for (int i = 0; i < pos - 1; i++) {
      cur = cur->next;
    }

    // add the value n times
    for (int i = 0; i < n; i++) {
      cur->next = new SLLNode(value, cur->next); // set the current node's next to new node
      cur = cur->next; // move pointer to new node
      listSize++;
    }

  }

}

template<typename T>
void SLList<T>::erase(unsigned pos) {
  if (pos > listSize - 1 || pos < 0) return; // is position is out of bounds do nothing
  if (pos == 0) {
    pop_front();
  }
  else if (pos == listSize - 1) {
    pop_back();
  }
  else {
    SLLNode<T>* cur = head;
    // find the node BEFORE the specified position
    for (int i = 0; i < pos - 1; i++) {
      cur = cur->next;
    }
    SLLNode<T>* to_delete = cur->next; // store the node at given position to delete later
    cur->next = cur->next->next; // connect cur node to the node AFTER its next, unlinking the node at given position
    delete to_delete;
    listSize--;
  }
}

template<typename T>
void SLList<T>::remove(const T& value) {
  SLLNode<T>* cur = head;
  int index = 0; // track the index so we can use as argument for erase()

  // loop through list
  while (cur != nullptr) {
    if (cur->data == value) {
      erase(index);
      index--; // subtract index to account for listSize decrementing
    }
    cur = cur->next;
    index++;
  }
}

template<typename T>
void SLList<T>::rotate_right(unsigned k) {
  if(listSize == 0 || k <= 0) return; // if empty or invalid rotation, do nothing
  for (int i = 0; i < k; i++) {
    // make last element the head, and make 2nd to last the tail
    SLLNode<T>* cur = head;
    // find the 2nd to last node
    while (cur->next != tail) {
      cur = cur->next;
    }
    cur->next = nullptr; // point 2nd to last node to nullptr, effectively making it the last node

    tail->next = head; // point current tail to current head

    head = tail; // tail is now the head

    tail = cur; // tail is now the (formerly) 2nd to last node

  }

}