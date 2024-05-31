#ifndef QUEUE_H
#define QUEUE_H
#include "DLList.h"

template<typename T>
class Queue {
public:
  Queue();
  // BIG THREE (destructor, copy, assignment)
  ~Queue();
  Queue(const Queue<T>& other);
  Queue<T>& operator=(const Queue<T>& other);
  

  unsigned size() const;
  bool empty() const;
  void print() const;
  
  void enqueue(const T& val); // add value to back of queue
  void dequeue(); // remove value from the front of queue
  void clear(); // empty the queue

  const T& front() const; // return the first element in queue (readonly)

private:
  DLList<T>* data; // pointer to linked list that holds data
};


#endif