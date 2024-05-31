#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue {
public:
  Queue(unsigned capacity = 10);

  unsigned size() const;
  bool empty() const;
  bool full() const;

  void clear();
  void enqueue(const T& val);
  void dequeue();
  const T& front() const;
  void print() const;

private:
  T* data;
  unsigned queueSize; //the actual number of elements in the queue
  unsigned capacity; //the max number of elements
  int frnt; //the index of the first element in the queue
  int bck; //the index of the last element in the queue

};


#endif